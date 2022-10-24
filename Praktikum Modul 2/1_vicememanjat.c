#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int num = 0;
int flag = 0;

typedef struct bstnode_t {
    int key;
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

void __bst__climb(BSTNode *root, int value, int arr[]) 
{
    int checkRoot = 0;

    while (root != NULL) 
    {
        if (checkRoot == 0)
        {
            if (value == root->key)
            {
                break;
            }

            checkRoot = 1;
        }

        arr[num] = root->key;
        num++;

        if (value < root->key)
        {
            root = root->left;
        }

        else if (value > root->key)
        {
            root = root->right;
        }

        else
        {
            if (root->left == NULL && root->right == NULL)
            {
                flag = 1;
            }

            break;
        }
    }
}

BSTNode* __bst__findMinNode(BSTNode *node) {
    BSTNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    
    return currNode;
}

BSTNode* __bst__remove(BSTNode *root, int value) {
    if (root == NULL) return NULL;

    if (value > root->key) 
        root->right = __bst__remove(root->right, value);
    else if (value < root->key) 
        root->left = __bst__remove(root->left, value);
    else {
        
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
        root->right   = __bst__remove(root->right, temp->key);
    }
    return root;
}

bool checkPrime(int n)
{
    if (n==2)
	{
		return true;
	}
	    
	else if (n==1 || n%2==0)
    {
        return false;
    }
    
    for (int i=3 ; i*i<=n ; i+=2)
    {
        if (n%i==0 && n/i!=1)
        {
            return false;
        }
    }

    return true;
}

void __bst__inordersemua(BSTNode *root) {
    if (root) {
        __bst__inordersemua(root->left);
        printf("%d\n", root->key);
        __bst__inordersemua(root->right);
    }
}

void __bst__inordergenap(BSTNode *root) {
    if (root) {
        __bst__inordergenap(root->left);
        if (root->key%2 == 0)
        {
            printf("%d\n", root->key);
        }
        __bst__inordergenap(root->right);
    }
}

void __bst__inorderganjil(BSTNode *root) {
    if (root) {
        __bst__inorderganjil(root->left);
        if (root->key%2 != 0)
        {
            printf("%d\n", root->key);
        }
        __bst__inorderganjil(root->right);
    }
}

void __bst__inorderprima(BSTNode *root) {
    if (root) {
        __bst__inorderprima(root->left);
        if (checkPrime(root->key) == 1)
        {
            printf("%d\n", root->key);
        }
        __bst__inorderprima(root->right);
    }
}

void __bst__postordersemua(BSTNode *root) {
    if (root) {
        __bst__postordersemua(root->left);
        __bst__postordersemua(root->right);
        printf("%d\n", root->key);
    }
}

void __bst__postorderganjil(BSTNode *root) {
    if (root) {
        __bst__postorderganjil(root->left);
        __bst__postorderganjil(root->right);
        if (root->key%2 != 0)
        {
            printf("%d\n", root->key);
        }
    }
}

void __bst__postordergenap(BSTNode *root) {
    if (root) {
        __bst__postordergenap(root->left);
        __bst__postordergenap(root->right);
        if (root->key%2 == 0)
        {
            printf("%d\n", root->key);
        }
    }
}

void __bst__postorderprima(BSTNode *root) {
    if (root) {
        __bst__postorderprima(root->left);
        __bst__postorderprima(root->right);
        if (checkPrime(root->key) == 1)
        {
            printf("%d\n", root->key);
        }
    }
}

void __bst__preordersemua(BSTNode *root) {
    if (root) {
        printf("%d\n", root->key);
        __bst__preordersemua(root->left);
        __bst__preordersemua(root->right);
    }
}

void __bst__preorderganjil(BSTNode *root) {
    if (root) {
        if (root->key%2 != 0)
        {
            printf("%d\n", root->key);
        }
        __bst__preorderganjil(root->left);
        __bst__preorderganjil(root->right);
    }
}

void __bst__preordergenap(BSTNode *root) {
    if (root) {
        if (root->key%2 == 0)
        {
            printf("%d\n", root->key);
        }
        __bst__preordergenap(root->left);
        __bst__preordergenap(root->right);
    }
}

void __bst__preorderprima(BSTNode *root) {
    if (root) {
        if (checkPrime(root->key) == 1)
        {
            printf("%d\n", root->key);
        }
        __bst__preorderprima(root->left);
        __bst__preorderprima(root->right);
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

void bst_climb(BST *bst, int value, int arr[]) {
    __bst__climb(bst->_root, value, arr);
}

void bst_insert(BST *bst, int value) {
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value);
        bst->_size++;
    }
}

void bst_remove(BST *bst, int value) {
    if (bst_find(bst, value)) {
        bst->_root = __bst__remove(bst->_root, value);
        bst->_size--;
    }
}

void bst_inordersemua(BST *bst) {
    __bst__inordersemua(bst->_root);
}

void bst_inorderganjil(BST *bst) {
    __bst__inorderganjil(bst->_root);
}

void bst_inordergenap(BST *bst) {
    __bst__inordergenap(bst->_root);
}

void bst_inorderprima(BST *bst) {
    __bst__inorderprima(bst->_root);
}

void bst_postordersemua(BST *bst) {
    __bst__postordersemua(bst->_root);
}

void bst_postorderganjil(BST *bst) {
    __bst__postorderganjil(bst->_root);
}

void bst_postordergenap(BST *bst) {
    __bst__postordergenap(bst->_root);
}

void bst_postorderprima(BST *bst) {
    __bst__postorderprima(bst->_root);
}

void bst_preordersemua(BST *bst) {
    __bst__preordersemua(bst->_root);
}

void bst_preorderganjil(BST *bst) {
    __bst__preorderganjil(bst->_root);
}

void bst_preordergenap(BST *bst) {
    __bst__preordergenap(bst->_root);
}

void bst_preorderprima(BST *bst) {
    __bst__preorderprima(bst->_root);
}
 
int main()
{
    BST set;
    bst_init(&set);

    int n, q, i;
    scanf("%d", &n);

    while (n != -1)
    {
        bst_insert(&set, n);
        scanf("%d", &n);
    }

    scanf("%d", &q);

    for (i = 0 ; i<q ; i++)
    {
        char command[20];
        scanf("%s", command);

        printf("Command : #%d\n", i+1);

        if (strcmp(command, "inorder") == 0)
        {
            char keterangan[20];
            scanf("%s", keterangan);

            if (strcmp(keterangan, "semua") == 0)
            {
                bst_inordersemua(&set);
            }

            else if (strcmp(keterangan, "ganjil") == 0)
            {
                bst_inorderganjil(&set);
            }

            else if (strcmp(keterangan, "genap") == 0)
            {
                bst_inordergenap(&set);
            }

            else if (strcmp(keterangan, "prima") == 0)
            {
                bst_inorderprima(&set);
            }
        }

        else if (strcmp(command, "postorder") == 0)
        {
            char keterangan[20];
            scanf("%s", keterangan);

            if (strcmp(keterangan, "semua") == 0)
            {
                bst_postordersemua(&set);
            }

            else if (strcmp(keterangan, "ganjil") == 0)
            {
                bst_postorderganjil(&set);
            }

            else if (strcmp(keterangan, "genap") == 0)
            {
                bst_postordergenap(&set);
            }

            else if (strcmp(keterangan, "prima") == 0)
            {
                bst_postorderprima(&set);
            }
        }

        else if (strcmp(command, "preorder") == 0)
        {
            char keterangan[20];
            scanf("%s", keterangan);

            if (strcmp(keterangan, "semua") == 0)
            {
                bst_preordersemua(&set);
            }

            else if (strcmp(keterangan, "ganjil") == 0)
            {
                bst_preorderganjil(&set);
            }

            else if (strcmp(keterangan, "genap") == 0)
            {
                bst_preordergenap(&set);
            }

            else if (strcmp(keterangan, "prima") == 0)
            {
                bst_preorderprima(&set);
            }
        }

        else if (strcmp(command, "panjat") == 0)
        {
            int val, arr[set._size], j;
            scanf("%d", &val);

            num = 0;
            flag = 0;
            bst_climb(&set, val, arr);

            if (flag == 1)
            {
                for (j = num - 1 ; j>=0 ; j--)
                {
                    printf("%d\n", arr[j]);
                }

                bst_remove(&set, val);
            }

            else
            {
                printf("Gabisa, dasar setan!\n");
            }
        }
    }

    return 0;
}