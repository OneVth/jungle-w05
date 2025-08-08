//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/// test function ///
void smokeTest(void);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
#ifdef DEBUG
	printf("[DEBUG MODE] Running test functions\n");
	smokeTest();
	return 0;
#endif

	LinkedList ll;
	int c, i, j;
	c = 1;
	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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

//////////////////////////////////////////////////////////////////////////////////

void smokeTest(void)
{
	printf("============== Smoke Test Start ==============\n\n");

#define TEST_COUNT 8
#define MAX_ELEMENTS 10

	int test_cases[TEST_COUNT][MAX_ELEMENTS] = {
		{2, 3, 4, 7, 5, 15, 18},
		{3, 5, 7, 9},
		{2, 4, 6, 8},
		{3, 4, 7, 5, 15, 18},
		{1, 2, 4},
		{2, 4, 3},
		{1, 3, 5},
		{2, 4, 6},
	};

	int test_sizes[TEST_COUNT] = {7, 4, 4, 6, 3, 3, 3, 3};

	for (int i = 0; i < TEST_COUNT; i++)
	{
		printf("**************** test case %02d ****************\n", i + 1);
		LinkedList ll;

		// Initialize the linked list 1 as an empty linked list
		ll.head = NULL;
		ll.size = 0;

		for (int j = 0; j < test_sizes[i]; j++)
			insertNode(&ll, j, test_cases[i][j]);

		printf("\nbefore move: ");
		printList(&ll);

		moveOddItemsToBack(&ll);

		printf("\nafter move: ");
		printList(&ll);

		removeAllItems(&ll);
		putchar('\n');
	}

	printf("============= Smoke Test Complete =============\n");
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	// ll에 노드가 하나 있으면 함수를 실행할 필요 없음
	if (ll == NULL || ll->size < 2)
		return;

	ListNode *cur = ll->head;
	ListNode *prev = NULL;
	for (int i = 0; i < ll->size; i++)
	{
		if (cur->item % 2 == 1)
		{
			// 대상 노드가 head일 경우 head 최신화 필요
			if (cur == ll->head)
			{
				ListNode *ptr = findNode(ll, ll->size - 1);
				ll->head = cur->next;
				cur->next = NULL;
				ptr->next = cur;
				cur = ll->head;
			}
			else
			{
				ListNode *ptr = findNode(ll, ll->size - 1);
				prev->next = cur->next;
				ptr->next = cur;
				cur->next = NULL;
				cur = prev->next;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

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
