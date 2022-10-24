#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int flag = 0, total;

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

AVLNode *mainroot, *par;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
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

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
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

void _searchParent(AVLNode *root, int value, int parent) 
{
    if (root == NULL)
        return;
 
    if (root->data == value) 
    {
        par = root;
    }

    else 
    {
        _searchParent(root->left, value, root->data);
        _searchParent(root->right, value, root->data);
    }
}

void preorder(AVLNode *root, int count, int before) 
{
    if (root && flag == 0) 
    {
        count += root->data;
        if (count == total)
        {
            flag = 1;
            return;
        }

        par = NULL;
        _searchParent(mainroot, root->data, -1);
        
        if (par)
        {
            if (par->data != before)
            {
                preorder(par, count, root->data);
            }
        }
        
        if (root->left)
        {
            if (root->left->data != before)
            {
                preorder(root->left, count, root->data);
            }
        }
        
        if (root->right)
        {
            if (root->right->data != before)
            {
                preorder(root->right, count, root->data);
            }
        }
    }
}

void traverse (AVLNode *root) 
{
    if (root) 
    {
        par = NULL;
        _searchParent(mainroot, root->data, -1);

        preorder(par, 0, root->data);
        preorder(root, 0, root->data);
        preorder(root->left, 0, root->data);
        preorder(root->right, 0, root->data);
        traverse(root->left);
        traverse(root->right);
    }
}

int main()
{
    AVL avlku;
    avl_init(&avlku);

    int n, sum = 0;
    scanf("%d", &n);
    
    while (n--) 
    {
        int q, num;
        scanf("%d%d", &q, &num);

        if (q == 1)
        {
            sum += num;
            avl_insert(&avlku, num);
        }

        else if (q == 2)
        {
            if (num >= sum)
            {
                printf("Apasi, ngajak berantem mulu dah kerjaannya:(\n");
            }

            else
            {
                if (avl_find(&avlku, num))
                {
                    printf("Aaa udh lama bgt ga diboongin:)\n");
                }

                else
                {
                    flag = 0;
                    total = num;
                    mainroot = avlku._root;

                    traverse(mainroot);

                    if (flag == 1)
                    {
                        printf("Aaa udh lama bgt ga diboongin:)\n");
                    }

                    else
                    {
                        printf("Apasi, ngajak berantem mulu dah kerjaannya:(\n");
                    }
                }
            }
        }
    }
}