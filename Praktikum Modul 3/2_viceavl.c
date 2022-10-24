#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int arr[3], x = 0;

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) 
{
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

void _requiemPrint(AVLNode *root, int value, int h) 
{
    while (root != NULL) 
    {
        if (root->height - h < 3)
        {
            arr[x] = root->data;
            x++;
        }

        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return;
    }

    return;
}

void avl_requiem(AVL *avl, int value) 
{
    AVLNode *temp = _search(avl->_root, value);
    int height = temp->height;

    if (temp == NULL)
        return;
    
    else if (temp->data == value)
    {
        _requiemPrint(avl->_root, value, height);
        for (int i = 2; i >= 0 ; i--) 
        {
            if (arr[i] != -1)
            {
                printf("%d\n", arr[i]);
            }
        }
    }
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

AVLNode* _rightRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value) {
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
    	node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data) // skewed kiri (left-left case)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data) // 
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void preorder(AVLNode *root, int value) 
{
    if (root) 
    {
        if (root->data == value)
        {
            printf("%d", root->data);
        }

        else
        {
            printf(":%d", root->data);
        } 

        preorder(root->left, value);
        preorder(root->right, value);
    }
}

int main()
{
    AVL avlku;
    avl_init(&avlku);

    while(1)
    {
        char command[7];
        scanf("%s", command);

        if (strcmp(command, "add") == 0)
        {
            int num;
            scanf("%d", &num);
            avl_insert(&avlku, num);
        }

        else if (strcmp(command, "more:") == 0)
        {
            char command2[10];
            getchar();
            scanf("%s", command2);

            if (strcmp(command2, "requiem") == 0)
            {
                int num;
                scanf("%d", &num);

                for (int i = 0; i < 3; i++)
                {
                    arr[i] = -1;
                }
                x = 0;

                printf("requiem:\n");
                avl_requiem(&avlku, num);
            }

            else if (strcmp(command2, "finish") == 0)
            {
                printf("list:\n");
                preorder(avlku._root, avlku._root->data);
                return 0;
            }
        }
    }
}