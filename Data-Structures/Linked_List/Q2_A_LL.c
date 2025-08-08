//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/// test function ///
void smokeTest(void);
void test_wrapping(void);
void testCase1(void);
void testCase2(void);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
#ifdef DEBUG
	printf("[DEBUG MODE] Running test functions\n");
	smokeTest();
	return 0;
#endif

	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	// Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
			printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
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

#define TEST_COUNT 7
#define MAX_ELEMENTS 10

	int test_cases1[TEST_COUNT][MAX_ELEMENTS] = {
		{1, 2, 3},
		{1, 5, 7, 3, 9, 11},
		{1, 2, 3},
		{},
		{1, 2, 3},
		{1, 2, 3},
		{1, 2},
	};
	int test_sizes1[TEST_COUNT] = {3, 6, 3, 0, 3, 3, 2};

	int test_cases2[TEST_COUNT][MAX_ELEMENTS] = {
		{4, 5, 6, 7},
		{6, 10, 2, 4},
		{},
		{1, 2, 3},
		{5},
		{4, 5, 6},
		{5, 6, 7, 8}};
	int test_sizes2[TEST_COUNT] = {4, 4, 0, 3, 1, 3, 4};

	for (int i = 0; i < TEST_COUNT; i++)
	{
		printf("**************** test case %02d ****************\n", i + 1);
		LinkedList ll1, ll2;

		// Initialize the linked list 1 as an empty linked list
		ll1.head = NULL;
		ll1.size = 0;

		// Initialize the linked list 2 as an empty linked list
		ll2.head = NULL;
		ll2.size = 0;

		for (int j = 0; j < test_sizes1[i]; j++)
			insertNode(&ll1, j, test_cases1[i][j]);

		for (int j = 0; j < test_sizes2[i]; j++)
			insertNode(&ll2, j, test_cases2[i][j]);

		printf("\nbefore merge:\n");
		printf("LinkedList1: ");
		printList(&ll1);
		printf("LinkedList2: ");
		printList(&ll2);

		alternateMergeLinkedList(&ll1, &ll2);

		printf("\nafter merge:\n");
		printf("LinkedList1: ");
		printList(&ll1);
		printf("LinkedList2: ");
		printList(&ll2);

		removeAllItems(&ll1);
		removeAllItems(&ll2);
		putchar('\n');
	}

	printf("============= Smoke Test Complete =============\n");
}

void test_wrapping(void)
{
	testCase1();
	testCase2();
}

void testCase1(void)
{
	printf("**************** test case 1 ****************\n");
	LinkedList ll1, ll2;

	// Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	insertNode(&ll1, 0, 1);
	insertNode(&ll1, 1, 2);
	insertNode(&ll1, 2, 3);

	insertNode(&ll2, 0, 4);
	insertNode(&ll2, 1, 5);
	insertNode(&ll2, 2, 6);
	insertNode(&ll2, 3, 7);

	printf("\nbefore merge:\n");
	printf("LinkedList1: ");
	printList(&ll1);
	printf("LinkedList1: ");
	printList(&ll2);

	alternateMergeLinkedList(&ll1, &ll2);

	printf("\nafter merge: ");
	printf("LinkedList1: ");
	printList(&ll1);
	printf("LinkedList1: ");
	printList(&ll2);

	removeAllItems(&ll1);
	removeAllItems(&ll2);
	putchar('\n');
}

void testCase2(void)
{
	printf("**************** test case 2 ****************\n");
	LinkedList ll1, ll2;

	// Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	insertNode(&ll1, 0, 1);
	insertNode(&ll1, 1, 5);
	insertNode(&ll1, 2, 7);
	insertNode(&ll1, 3, 3);
	insertNode(&ll1, 4, 9);
	insertNode(&ll1, 5, 11);

	insertNode(&ll2, 0, 6);
	insertNode(&ll2, 1, 10);
	insertNode(&ll2, 2, 2);
	insertNode(&ll2, 3, 4);

	printf("\nbefore merge:\n");
	printf("LinkedList1: ");
	printList(&ll1);
	printf("LinkedList1: ");
	printList(&ll2);

	alternateMergeLinkedList(&ll1, &ll2);

	printf("\nafter merge: ");
	printf("LinkedList1: ");
	printList(&ll1);
	printf("LinkedList1: ");
	printList(&ll2);

	removeAllItems(&ll1);
	removeAllItems(&ll2);
	putchar('\n');
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	int loop_cnt = 0;
	if (ll1->size >= ll2->size)
		loop_cnt = ll2->size;
	else
		loop_cnt = ll1->size;

	for (int i = 0; i < 2 * loop_cnt; i += 2)
	{
		insertNode(ll1, i + 1, ll2->head->item);
		removeNode(ll2, 0);
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
