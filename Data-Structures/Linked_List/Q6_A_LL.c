//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/// test functions ///
void smokeTest(void);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
#ifdef DEBUG
	printf("[DEBUG MODE] Running test functions\n");
	smokeTest();
	return 0;
#endif

	int c, i, j;
	c = 1;

	LinkedList ll;
	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head)); // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void smokeTest(void)
{
	printf("============== Smoke Test Start ==============\n\n");

#define TEST_COUNT 6
#define MAX_ELEMENTS 10

	int test_cases[TEST_COUNT][MAX_ELEMENTS] = {
		{30, 20, 40, 70, 50},
		{30, 50, 70, 90},
		{80, 60, 40, 20},
		{7, 1, 2, 3},
		{1, 2, 3, 4},
		{1, 2},
	};

	int test_sizes[TEST_COUNT] = {5, 4, 4, 4, 4, 2};

	for (int i = 0; i < TEST_COUNT; i++)
	{
		printf("**************** test case %02d ****************\n", i + 1);
		LinkedList ll;

		// Initialize the linked list 1 as an empty linked list
		ll.head = NULL;
		ll.size = 0;

		for (int j = 0; j < test_sizes[i]; j++)
			insertNode(&ll, j, test_cases[i][j]);

		printf("\nbefore exchange: ");
		printList(&ll);

		moveMaxToFront(&(ll.head));

		printf("\nafter exchange: ");
		printList(&ll);

		removeAllItems(&ll);
		putchar('\n');
	}

	printf("============= Smoke Test Complete =============\n");
}

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
	// 노드가 없거나 노드가 하나만 있는 리스트라면 함수를 실행할 필요 없음
	if (ptrHead == NULL || (*ptrHead)->next == NULL)
		return -1;

	ListNode *max_node = *ptrHead;
	ListNode *max_prev = NULL;

	ListNode *ptr = (*ptrHead)->next;
	ListNode *prev = *ptrHead;
	while (ptr != NULL)
	{
		if (ptr->item > max_node->item)
		{
			max_node = ptr;
			max_prev = prev;
		}
		prev = ptr;
		ptr = ptr->next;
	}

	// max_node가 리스트의 첫 노드라면 교환할 필요 없음
	if (max_node != *ptrHead)
	{
		max_prev->next = max_node->next;
		max_node->next = *ptrHead;
		*ptrHead = max_node;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
