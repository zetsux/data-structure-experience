#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;
    struct Tree *left; 
    struct Tree *right;
} Tree;

void create(Tree **pohon)
{
    *pohon = NULL;
}

void clear(Tree **pohon)
{
    *pohon = NULL;
}

int isEmpty(Tree **pohon)
{
    if (*pohon == NULL)
    {
        return 1;
    }

    return 0;
}

void insert(Tree **root, int newData)
{
    if (isEmpty(root) == 1)
    {
        Tree *new;
        new = (Tree*) malloc(sizeof(Tree));
        new->data = newData;
        new->left = new->right = NULL;
        *root = new;
        (*root)->left = (*root)->right = NULL;
    }

    else if (newData < (*root)->data)
    {
        insert(&(*root)->left, newData);
    }

    else if (newData > (*root)->data)
    {
        insert(&(*root)->right, newData);
    }

    else if (newData == (*root)->data)
    {
        printf("Data %d sudah ada dalam Tree!", newData);
    }
}

void preOrder(Tree **root)
{
    if ((*root) != NULL)
    {
        printf("%d ", (*root)->data);
        preOrder(&(*root)->left);
        preOrder(&(*root)->right);
    }
}

void inOrder(Tree **root)
{
    if ((*root) != NULL)
    {
        inOrder(&(*root)->left);
        printf("%d ", (*root)->data);
        inOrder(&(*root)->right);
    }
}

void postOrder(Tree **root)
{
    if ((*root) != NULL)
    {
        postOrder(&(*root) ->left);
        postOrder(&(*root) ->right);
        printf("%d ", (*root) ->data);
    }
}

int main()
{
    Tree *pohon;

    create(&pohon);

    insert(&pohon, 2);
    insert(&pohon, 3);
    insert(&pohon, 1);
    insert(&pohon, 5);
    insert(&pohon, 4);

    preOrder(&pohon);
    puts("");
    inOrder(&pohon);
    puts("");
    postOrder(&pohon);
    puts("");

    clear(&pohon);
    inOrder(&pohon);
    puts("");
}