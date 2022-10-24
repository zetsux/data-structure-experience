#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int min = -1;

typedef struct bstnode_t {
    int key;
    int index;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

typedef struct stackNode_t {
    BSTNode *_root;
    struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
    StackNode *_top;
} Stack;

void stack_init(Stack *stack) 
{
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) 
{
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, BSTNode *root) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) 
    {
        newNode->_root = root;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

BSTNode* stack_pop(Stack *stack) 
{
    StackNode *temp = stack->_top;
    BSTNode *ret = stack->_top->_root;
    stack->_top = stack->_top->next;
    free(temp);
    return ret;
}

BSTNode* __bst__createNode(int value, int value2) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->index = value2;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int value2) {
    if (root == NULL) 
        return __bst__createNode(value, value2);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, value2);
    else if (value >= root->key)
        root->right = __bst__insert(root->right, value, value2);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
    while (root != NULL) {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value, int index) {
    if (root == NULL) return NULL;

    if (value > root->key || (value == root->key && root->index != index)) 
        root->right = __bst__remove(root->right, value, index);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value, index);
    else 
    {
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        }
        else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = __bst__findMinNode(root->right);
        root->key     = temp->key;
        root->index   = temp->index;
        root->right   = __bst__remove(root->right, temp->key, temp->index);
    }
    return root;
}

void __bst__minimum(BSTNode *root, int a, int b) 
{
    BSTNode *current = root;

    Stack tempStack;
    stack_init(&tempStack);

    int done = 0;

    while (done != 1)
    {
        if (current != NULL)
        {
            stack_push(&tempStack, current);
            current = current->left;
        }

        else
        {
            if (!stack_isEmpty(&tempStack))
            {
                current = stack_pop(&tempStack);
                if (current->index >= a && current->index <= b && min == -1)
                {
                    min = current->key;
                    return;
                }
                current = current->right;
            }

            else
            {
                done = 1;
            }
        }
    }
}

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) {
    return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_insert(BST *bst, int value, int value2) 
{
    bst->_root = __bst__insert(bst->_root, value, value2);
    bst->_size++;
}

void bst_remove(BST *bst, int value, int index) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value, index);
        bst->_size--;
    }
}

void bst_minimum(BST *bst, int a, int b) 
{
    __bst__minimum(bst->_root, a, b);
}
 
int main()
{
    BST set;
    bst_init(&set);

    int n, q, i;
    scanf("%d", &n);

    int arr[n];

    for (i = 0 ; i<n ; i++)
    {
        int x;
        scanf("%d", &x);

        arr[i] = x;
        bst_insert(&set, x, i);
    }

    scanf("%d", &q);

    for (i = 0 ; i<q ; i++)
    {
        int command, var1, var2;
        scanf("%d%d%d", &command, &var1, &var2);

        if (command == 1)
        {
            bst_remove(&set, arr[var1], var1);
            arr[var1] = var2;
            bst_insert(&set, var2, var1);
        }

        else if (command == 2)
        {
            if (var2 - var1 < 300)
            {
                int j, minarr = 1500;

                for (j = var1 ; j<=var2 ; j++)
                {
                    if (arr[j] < minarr)
                    {
                        minarr = arr[j];
                    }
                }

                printf("%d\n", minarr);
            }

            else
            {
                bst_minimum(&set, var1, var2);

                printf("%d\n", min);
                min = -1;
            }
        }
    }
}