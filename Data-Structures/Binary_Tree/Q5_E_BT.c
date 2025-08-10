//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;


///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void mirrorTree(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push( Stack *stack, BTNode *node);
BTNode* pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

/// test function ///
void smokeTest(void);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
#ifdef DEBUG
    printf("[DEBUG MODE] Running test functions\n");
    smokeTest();
    return 0;
#endif
    char e;
    int c;
    BTNode *root;

    c = 1;
    root = NULL;


    printf("1: Create a binary tree.\n");
    printf("2: Mirror the binary tree.\n");
    printf("0: Quit;\n");


    while(c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if( scanf("%d",&c) > 0)
        {
            switch(c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                mirrorTree(root);
                printf("Mirror binary tree is: ");
                printTree(root);
                printf("\n");
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void smokeTest(void)
{
    printf("============== Smoke Test Start ==============\n\n");

#define TEST_COUNT 7
#define MAX_ELEMENTS 100

    int test_cases[TEST_COUNT][MAX_ELEMENTS] = {
        {4, 5, 2, 0, 6, 0, 0, 3, 1, 0, 0, 0, 0},
        {50, 40, 60, 11, 35, 0, 0, 0, 0, 80, 85, 0, 0, 0, 0},
        {50, 20, 60, 10, 30, 0, 0, 55, 0, 0, 80, 0, 0, 0, 0},
        {4, 2, 6, 1, 3, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0},
        {5, 3, 7, 1, 2, 9, 0, 0, 0, 0, 0, 4, 8, 0, 0, 0, 0},
        {1, 2, 3, 0, 0, 4, 5, 0, 0, 0, 0},
        {1, 2, 3, 0, 0, 0, 0},
    };

    int test_sizes[TEST_COUNT] = {13, 15, 15, 15, 15, 11, 7};

    for (int i = 0; i < TEST_COUNT; i++)
    {
        printf("**************** test case %02d ****************\n", i + 1);
        Stack stk;
        BTNode *root, *temp;

        stk.top = NULL;
        root = NULL;

        root = createBTNode(test_cases[i][0]);
        push(&stk, root);

        for (int j = 1; j < test_sizes[i]; j++)
        {
            temp = pop(&stk);
            if (test_cases[i][j] != 0)
                temp->left = createBTNode(test_cases[i][j]);
            if (test_cases[i][++j] != 0)
                temp->right = createBTNode(test_cases[i][j]);

            if (temp->right != NULL)
                push(&stk, temp->right);
            if (temp->left != NULL)
                push(&stk, temp->left);
        }

        printf("before mirror: ");
        printTree(root);
        putchar('\n');

        mirrorTree(root);

        printf("after mirror: ");
        printTree(root);
        putchar('\n');

        removeAll(&root);
        putchar('\n');
    }
    printf("============= Smoke Test Complete =============\n");
}

//////////////////////////////////////////////////////////////////////////////////

void mirrorTree(BTNode *node)
{
	if (node == NULL)
        return;

    BTNode* temp = node->left;
    node->left = node->right;
    node->right = temp;
    mirrorTree(node->left);
    mirrorTree(node->right);
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if(scanf("%d",&item) > 0)
    {
        root = createBTNode(item);
        push(&stack,root);
    }
    else
    {
        scanf("%c",&s);
    }

    while((temp =pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stack,temp->right);
        if(temp->left != NULL)
            push(&stack,temp->left);
    }
    return root;
}

void push( Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;
    if(stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode* pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if(top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if(*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}

