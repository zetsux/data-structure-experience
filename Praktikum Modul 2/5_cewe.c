#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int count = 0;

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

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value) {
    if (root == NULL) 
        return __bst__createNode(value);

    if (value < root->key)
        root->left = __bst__insert(root->left, value);
    else if (value >= root->key)
        root->right = __bst__insert(root->right, value);
    
    return root;
}

BSTNode* __bst__search(BSTNode *root, int value) {
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

BSTNode* __bst__searchparent(BSTNode *root, int value) {
    while (root != NULL) 
    {
        if (root->right != NULL)
        {
            if (root->right->key == value)
            {
                return root;
            }
        }

        else if (root->left != NULL)
        {
            if (root->left->key == value)
            {
                return root;
            }
        }
        
        if (value < root->key)
            root = root->left;
        else if (value > root->key)
            root = root->right;
    }
    return root;
}

void __bst__index(BSTNode *root, int value) 
{
    if (root) {
        __bst__index(root->left, value);
        count++;
        root->index = count;
        if (value == root->key)
        {
            printf("%d\n", count);
        }
        __bst__index(root->right, value);
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

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_index(BST *bst, int value) {
    __bst__index(bst->_root, value);
}

int bst_findindex(BST *bst, int value) 
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

int bst_findparent(BST *bst, int value) 
{
    BSTNode *temp = __bst__searchparent(bst->_root, value);

    if (temp == NULL)
        return -1;
    
    if (temp->right != NULL)
    {
        if (temp->right->key == value)
        {
            return temp->key;
        }
    }

    else if (temp->left != NULL)
    {
        if (temp->left->key == value)
        {
            return temp->key;
        }
    }
    
    return -1;
}
 
int main()
{
    BST set;
    bst_init(&set);

    int q, i, first = -1;
    scanf("%d", &q);
    getchar();

    for (i = 0 ; i<q ; i++)
    {
        char command[10];
        int var;
        scanf("%s", command);
        scanf("%d", &var);

        if (strcmp(command, "masukin") == 0)
        {
            if (first == -1)
            {
                first = var;
            }

            bst_insert(&set, var);
            count = 0;
        }

        else if (strcmp(command, "anaksiapa") == 0)
        {
            if (!bst_find(&set, var) || first == var)
            {
                printf("ini anak siapa dah\n");
                continue;
            }

            int func = bst_findparent(&set, var);

            if (func == -1)
            {
                printf("ini anak siapa dah\n");
            }

            else
            {
                printf("%d\n", func);
            }
        }

        else if (strcmp(command, "berapa") == 0)
        {
            int func = bst_findindex(&set, var);

            if (func == -1)
            {
                printf("Data tidak ada\n");
            }

            else if (func == 0)
            {
                bst_index(&set, var);
            }

            else
            {
                printf("%d\n", func);
            }
        }
    }

    return 0;
}