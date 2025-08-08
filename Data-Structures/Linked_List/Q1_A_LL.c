//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

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

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/// test function ///
void test_wrapping(void);
void testCase1(void);
void testCase2(void);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
#ifdef DEBUG
	printf("[DEBUG MODE] Running test functions\n");
	test_wrapping();
	return 0;
#endif

	LinkedList ll;
	int c, i, j;
	c = 1;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	

	// ********************************* origin ****************************************
	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}
	// ********************************* origin ****************************************
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void test_wrapping(void)
{
	testCase1();
	testCase2();
}

void testCase1(void)
{
	printf("**************** test case 1 ****************\n");
	LinkedList ll;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	insertNode(&ll, 0, 2);
	insertNode(&ll, 1, 3);
	insertNode(&ll, 2, 5);
	insertNode(&ll, 3, 7);
	insertNode(&ll, 4, 9);

	printf("\nbefore insertion: ");
	printList(&ll);

	printf("\ninserted index: %d\n", insertSortedLL(&ll, 8));

	printf("\nafter insertion: ");
	printList(&ll);

	removeAllItems(&ll);
	putchar('\n');
}

void testCase2(void)
{
	printf("**************** test case 2 ****************\n");
	LinkedList ll;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;
	
	insertNode(&ll, 0, 5);
	insertNode(&ll, 1, 7);
	insertNode(&ll, 2, 9);
	insertNode(&ll, 3, 11);
	insertNode(&ll, 4, 15);

	printf("\nbefore insertion: ");
	printList(&ll);

	printf("\ninserted index: %d\n", insertSortedLL(&ll, 7));

	printf("\nafter insertion: ");
	printList(&ll);

	removeAllItems(&ll);
	putchar('\n');
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	if (ll == NULL)
		return -1;
		
	ListNode *cur;

	// 연결 리스트가 비어 있을 때
	if (ll->head == NULL)
		return insertNode(ll, 0, item);

	int i = 0;
	cur = ll->head;
	while (cur != NULL)
	{
		if (cur->item == item)
			return -1;

		if (cur->item > item)
		{
			if (insertNode(ll, i, item) == 0)
				return i;
			else
				return -1;
		}
		cur = cur->next;
		i++;
	}

	// 연결 리스트 맨 끝에 삽입될 때
	if (insertNode(ll, ll->size, item) == 0)
		return ll->size - 1;
	return -1;
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
