//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

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

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stk, BTNode *node);
BTNode *pop(Stack *stk);

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
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/3/0): ");
        if (scanf("%d", &c) > 0)

        {

            switch (c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if (s)
                {
                    printf("Both trees are structurally identical.\n");
                }
                else
                {
                    printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c", &e);
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////

void smokeTest(void)
{
    printf("============== Smoke Test Start ==============\n\n");

#define TEST_COUNT 2
#define MAX_ELEMENTS 100

    int test_cases1[TEST_COUNT][MAX_ELEMENTS] = {
        {5, 3, 7, 1, 2, 0, 0, 0, 0, 4, 8, 0, 0, 0, 0},
        {1, 2, 3, 0, 0, 4, 5, 0, 0, 0, 0},
    };

    int test_cases2[TEST_COUNT][MAX_ELEMENTS] = {
        {5, 3, 7, 1, 2, 0, 0, 0, 0, 4, 8, 0, 0, 0, 0},
        {1, 2, 3, 0, 0, 4, 0},
    };

    int test_sizes1[TEST_COUNT] = {15, 11};
    int test_sizes2[TEST_COUNT] = {15, 7};

    for (int i = 0; i < TEST_COUNT; i++)
    {
        printf("**************** test case %02d ****************\n", i + 1);
        Stack stk_left, stk_right;
        BTNode *root_left, *root_right, *temp;

        stk_left.top = stk_right.top = NULL;
        root_left = root_right = NULL;

        root_left = createBTNode(test_cases1[i][0]);
        push(&stk_left, root_left);

        for (int j = 1; j < test_sizes1[i]; j++)
        {
            temp = pop(&stk_left);
            if (test_cases1[i][j] != 0)
                temp->left = createBTNode(test_cases1[i][j]);
            if (test_cases1[i][++j] != 0)
                temp->right = createBTNode(test_cases1[i][j]);

            if (temp->right != NULL)
                push(&stk_left, temp->right);
            if (temp->left != NULL)
                push(&stk_left, temp->left);
        }

        root_right = createBTNode(test_cases2[i][0]);
        push(&stk_right, root_right);

        for (int j = 1; j < test_sizes2[i]; j++)
        {
            temp = pop(&stk_right);
            if (test_cases2[i][j] != 0)
                temp->left = createBTNode(test_cases2[i][j]);
            if (test_cases2[i][++j] != 0)
                temp->right = createBTNode(test_cases2[i][j]);

            if (temp->right != NULL)
                push(&stk_right, temp->right);
            if (temp->left != NULL)
                push(&stk_right, temp->left);
        }

        printf("left tree: ");
        printTree(root_left);
        putchar('\n');

        printf("right tree: ");
        printTree(root_right);
        putchar('\n');

        if (identical(root_left, root_right))
            printf("Both trees are structurally identical.\n");
        else
            printf("Both trees are different.\n");

        removeAll(&root_left);
        removeAll(&root_right);
        putchar('\n');
    }
    printf("============= Smoke Test Complete =============\n");
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)

{
    if (tree1 == NULL && tree2 == NULL)
        return 1;

    if (tree1 == NULL || tree2 == NULL)
        return 0;

    if (tree1->item == tree2->item)
        return identical(tree1->left, tree2->left) && identical(tree1->right, tree2->right);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

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
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stk, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if (scanf("%d", &item) > 0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stk, temp->right);
        if (temp->left != NULL)
            push(&stk, temp->left);
    }
    return root;
}

void push(Stack *stk, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stk->top == NULL)
    {
        stk->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stk->top;
        stk->top = temp;
    }
}

BTNode *pop(Stack *stk)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stk->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stk->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
