#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int count = 0;

typedef struct bstnode_t {
    long long key;
    long long index;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    long long _size;
} BST;

BSTNode* __bst__createNode(long long value, long long index) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->index = index;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, long long value, long long index) 
{
    if (root == NULL) 
        return __bst__createNode(value, index);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, index);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, index);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, long long value) {
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

void __bst__index(BSTNode *root, long long value) 
{
    if (root) {
        __bst__index(root->right, value);
        count++;
        root->index = count;
        if (value == root->key)
        {
            printf("%d\n", count);
        }
        __bst__index(root->left, value);
    }
}

void bst_init(BST *bst) 
{
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_isEmpty(BST *bst) 
{
    return bst->_root == NULL;
}

long long bst_find(BST *bst, long long value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return -1;
    
    if (temp->key == value && count > 0)
    {
        return temp->index;
    }
    else if (temp->key == value)
        return 0;
    else
        return -1;
}

void bst_insert(BST *bst, long long value, long long index) 
{
    if (bst_find(bst, value) == -1) {
        bst->_root = __bst__insert(bst->_root, value, index);
        bst->_size++;
    }
}

void bst_index(BST *bst, long long value) {
    __bst__index(bst->_root, value);
}
 
int main()
{
    BST set;
    bst_init(&set);

    int q, i;
    scanf("%d", &q);

    for (i = 0 ; i<q ; i++)
    {
        int command;
        long long num;
        scanf("%d%lld", &command, &num);

        if (command == 1)
        {
            bst_insert(&set, num, 0);
            count = 0;
        }

        else if (command == 2)
        {
            long long func = bst_find(&set, num);

            if (func == -1)
            {
                printf("Data tidak ada\n");
            }

            else if (func == 0)
            {
                bst_index(&set, num);
            }

            else
            {
                printf("%lld\n", func);
            }
        }
    }
    
    return 0;
}