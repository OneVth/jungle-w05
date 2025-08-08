//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

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
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

/// test functions ///
void test_wrapping(void);
void testCase1(void);
void testCase2(void);
void testCase3(void);
void testCase4(void);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
#ifdef DEBUG
	printf("[DEBUG MODE] Running test functions\n");
	test_wrapping();
	return 0;
#endif
	int c, i;
	c = 1;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
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
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void test_wrapping(void)
{
	testCase1();
	testCase2();
	testCase3();
	testCase4();
}

static void test_util(LinkedList *ll, LinkedList *ll_front, LinkedList *ll_back)
{
	printf("\nbefore split:\n");
	printf("given list: ");
	printList(ll);
	printf("front list: ");
	printList(ll_front);
	printf("back list: ");
	printList(ll_back);

	frontBackSplitLinkedList(ll, ll_front, ll_back);

	printf("\nafter split:\n");
	printf("given list: ");
	printList(ll);
	printf("front list: ");
	printList(ll_front);
	printf("back list: ");
	printList(ll_back);
}

void testCase1(void)
{
	printf("**************** test case 1 ****************\n");
	LinkedList ll, ll_front, ll_back;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll_front.head = NULL;
	ll_front.size = 0;

	// Initialize the linked list 3 as an empty linked list
	ll_back.head = NULL;
	ll_back.size = 0;

	insertNode(&ll, 0, 2);
	insertNode(&ll, 1, 3);
	insertNode(&ll, 2, 4);
	insertNode(&ll, 3, 7);
	insertNode(&ll, 4, 5);
	insertNode(&ll, 5, 15);
	insertNode(&ll, 6, 18);

	test_util(&ll, &ll_front, &ll_back);

	removeAllItems(&ll);
	removeAllItems(&ll_front);
	removeAllItems(&ll_back);
	putchar('\n');
}

void testCase2(void)
{
	printf("**************** test case 2 ****************\n");
	LinkedList ll, ll_front, ll_back;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll_front.head = NULL;
	ll_front.size = 0;

	// Initialize the linked list 3 as an empty linked list
	ll_back.head = NULL;
	ll_back.size = 0;

	insertNode(&ll, 0, 3);
	insertNode(&ll, 1, 5);
	insertNode(&ll, 2, 7);
	insertNode(&ll, 3, 9);

	test_util(&ll, &ll_front, &ll_back);

	removeAllItems(&ll);
	removeAllItems(&ll_front);
	removeAllItems(&ll_back);
	putchar('\n');
}

void testCase3(void)
{
	printf("**************** test case 3 ****************\n");
	LinkedList ll, ll_front, ll_back;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll_front.head = NULL;
	ll_front.size = 0;

	// Initialize the linked list 3 as an empty linked list
	ll_back.head = NULL;
	ll_back.size = 0;

	insertNode(&ll, 0, 2);

	test_util(&ll, &ll_front, &ll_back);

	removeAllItems(&ll);
	removeAllItems(&ll_front);
	removeAllItems(&ll_back);
	putchar('\n');
}

void testCase4(void)
{
	printf("**************** test case 4 ****************\n");
	LinkedList ll, ll_front, ll_back;

	// Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the linked list 2 as an empty linked list
	ll_front.head = NULL;
	ll_front.size = 0;

	// Initialize the linked list 3 as an empty linked list
	ll_back.head = NULL;
	ll_back.size = 0;

	insertNode(&ll, 0, 2);
	insertNode(&ll, 1, 3);
	insertNode(&ll, 2, 5);
	insertNode(&ll, 3, 6);
	insertNode(&ll, 4, 7);

	test_util(&ll, &ll_front, &ll_back);

	removeAllItems(&ll);
	removeAllItems(&ll_front);
	removeAllItems(&ll_back);
	putchar('\n');
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	if (ll == NULL || ll->size <= 0)
		return;

	// resultFrontList, resultBackList가 비어있지 않으면 초기화
	if (resultFrontList != NULL)
		removeAllItems(resultFrontList);
	if (resultBackList != NULL)
		removeAllItems(resultBackList);

	int mid = 0;
	if (ll->size % 2 == 0)
		mid = ll->size / 2;
	else
		mid = ll->size / 2 + 1;
	
	ListNode *ptr = ll->head;
	for (int i = 0; i < mid; i++)
	{
		insertNode(resultFrontList, i, ptr->item);
		ptr = ptr->next;
	}

	for (int i = 0; i < ll->size - mid; i++)
	{
		insertNode(resultBackList, i, ptr->item);
		ptr = ptr->next;
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
