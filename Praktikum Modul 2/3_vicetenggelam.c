#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int lowest = 0;

typedef struct bstnode_t {
    int key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) 
{
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) 
{
    while (root != NULL) 
    {
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
}

void __bst__searchlowest(BSTNode* root, int level, int x)
{
    if (root == NULL)
        return;

    if (level == 1)
    {
        if (root->left == NULL && root->right == NULL)
        {
            if (root->key != x)
            {
                lowest = root->key;
                return;
            }
        }
    }

    else if (level > 1) 
    {
        __bst__searchlowest(root->left, level - 1, x);
        __bst__searchlowest(root->right, level - 1, x);
    }
}

int __bst__depth(BSTNode* root)
{
    if (root == NULL)
        return 0;

    else 
    {
        int left = __bst__depth(root->left);
        int right = __bst__depth(root->right);
 
        if (left > right) 
        {
            return (left + 1);
        }

        else 
        {
            return (right + 1);
        }
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

bool bst_find(BST *bst, int value) 
{
    BSTNode *temp = __bst__search(bst->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->key == value)
        return true;
    else
        return false;
}

void bst_lowest(BST *bst, int level, int x) 
{
    __bst__searchlowest(bst->_root, level, x);
}

int bst_depth(BST *bst)
{
    return __bst__depth(bst->_root);
}

void bst_insert(BST *bst, int value) 
{
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}
 
int main()
{
    BST set;
    bst_init(&set);

    int n, i, start = 0;
    scanf("%d", &n);

    for (i = 0 ; i<n ; i++)
    {
        int x, sum = 0;
        scanf("%d", &x);

        bst_insert(&set, x);

        if (start == 0)
        {
            printf("Mulai!\n");
            start = 1;
            continue;
        }

        int depth = bst_depth(&set);
        lowest = 0;
        bst_lowest(&set, depth, -1);
        sum = depth - 1;
        int flag = lowest;

        while (lowest == flag && depth >= 0)
        {
            bst_lowest(&set, depth, flag);
            depth--;
        }

        if (depth == -1)
        {
            depth = 0;
        }

        sum += depth;

        if (sum%2 == 0)
        {
            printf("IKKI!!! :(\n");
        }

        else
        {
            printf("%d\n", sum);
        }
    }

    return 0;
}