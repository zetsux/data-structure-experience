#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t {
    int key;
    char name[100];
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value, char* naming) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    strcpy(newNode->name, naming);
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, char* naming) 
{
    if (root == NULL) 
        return __bst__createNode(value, naming);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, naming);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, naming);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) 
{
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

BSTNode* __bst__searchcity(BSTNode *root, int x, int y) 
{
    while (root != NULL) 
    {
        if (x < root->key && y < root->key)
            root = root->left;
        else if (x > root->key && y > root->key)
            root = root->right;
        else
            return root;
    }
    return root;
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

char* bst_findcity(BST *bst, int x, int y) 
{
    BSTNode *temp = __bst__searchcity(bst->_root, x, y);
    return temp->name;
}

void bst_insert(BST *bst, int value, char* naming) 
{
    if (!bst_find(bst, value)) 
    {
        bst->_root = __bst__insert(bst->_root, value, naming);
        bst->_size++;
    }
}
 
int main()
{
    BST set;
    bst_init(&set);

    int n, i;
    scanf("%d", &n);
    getchar();

    for (i = 0 ; i<n ; i++)
    {
        int num;
        char kota[100];
        scanf("%d", &num);
        getchar();
        scanf("%s", kota);

        bst_insert(&set, num, kota);
    }

    scanf("%d", &n);

    for (i = 0 ; i<n ; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);

        printf("%s\n", bst_findcity(&set, x, y));
    }

    return 0;
}