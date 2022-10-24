#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int success, currentHealth, ybagDukun, ybagHealth;

typedef struct bstnode_t {
    int key;
    int key2;
    int sil;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value, int value2, int value3) 
{
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->key2 = value2;
    newNode->sil = value3;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int value2, int value3) {
    if (root == NULL) 
        return __bst__createNode(value, value2, value3);

    if (value < root->key)
        root->left = __bst__insert(root->left, value, value2, value3);
    else if (value > root->key)
        root->right = __bst__insert(root->right, value, value2, value3);
    
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

void __bst__simulator(BSTNode *root, int ybagPower) 
{
    if (root) 
    {
        __bst__simulator(root->left, ybagPower);
        __bst__simulator(root->right, ybagPower);

        if (ybagDukun <= 0)
        {
            success = 0;
        }

        else if (root->key2 < ybagPower)
        {
            if (root->sil == 1)
            {
                currentHealth += root->key;
            }
        }

        else if (root->key2 >= ybagPower)
        {
            currentHealth -= root->key2;

            if (currentHealth <= 0)
            {
                if (ybagDukun > 0)
                {
                    currentHealth = ybagHealth;
                    ybagDukun--;
                }

                else
                {
                    success = 0;
                }
            }
        }
    }
}

void __bst__real(BSTNode *root, int ybagPower) 
{
    if (root) 
    {
        __bst__real(root->left, ybagPower);
        __bst__real(root->right, ybagPower);

        if (ybagDukun <= 0)
        {
            printf("Ybag gagal sebelum lawan %d\n", root->key);
        }

        else if (root->key2 < ybagPower)
        {
            if (root->sil == 1)
            {
                printf("Kerbau %d membuat Ybag semakin posesif\n", root->key);
                currentHealth += root->key;
            }

            else if (root->sil == 0)
            {
                printf("Jujur Jd canggung bgt lawan setelah lawan kerbau %d\n", root->key);
            }
        }

        else if (root->key2 >= ybagPower)
        {
            if (root->sil == 1)
            {
                printf("Kerbau %d membuat Ybag kewalahan\n", root->key);
            }

            else if (root->sil == 0)
            {
                printf("udah deh, gausa cari perkara lawan kerbau %d\n", root->key);
            }

            currentHealth -= root->key2;

            if (currentHealth <= 0)
            {
                if (ybagDukun > 0)
                {
                    currentHealth = ybagHealth;
                    ybagDukun--;
                }
            }
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

void bst_insert(BST *bst, int value, int value2, int value3) 
{
    if (!bst_find(bst, value)) {
        bst->_root = __bst__insert(bst->_root, value, value2, value3);
        bst->_size++;
    }
}

int main()
{
    int n, t, i;
    scanf("%d%d", &n, &t);

    BST set;
    bst_init(&set);

    bst_insert(&set, 50000, 696969, 0);

    for (i = 0 ; i<n ; i++)
    {
        int keboHealth, keboPower, keboVersion;

        scanf("%d%d%d", &keboHealth, &keboVersion, &keboPower);
        bst_insert(&set, keboHealth, keboPower, keboVersion);
    }

    for (i = 0 ; i<t ; i++)
    {
        int ybagPower;
        scanf("%d%d%d", &ybagHealth, &ybagPower, &ybagDukun);

        currentHealth = ybagHealth;
        int suksesDukun = ybagDukun;
        success = 1;

        __bst__simulator(set._root->left, ybagPower);
        if (success == 1)
        {
            __bst__simulator(set._root->right, ybagPower);
        }

        if ((success == 1 && ybagDukun > 0) || i == t - 1)
        {
            ybagDukun = suksesDukun;
            currentHealth = ybagHealth;
            
            __bst__real(set._root->left, ybagPower);
            __bst__real(set._root->right, ybagPower);
            
            if (ybagDukun <= 0)
            {
                printf("gajadi gapapa_-\n");
            }

            else
            {
                printf("Makasi banya ya:)\n");
            }
            
            return 0;
        }
    }
}