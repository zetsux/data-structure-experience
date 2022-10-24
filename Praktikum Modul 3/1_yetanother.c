#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int prev = 1;
long long factorial = 1;

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
    int leftChild;
    int rightChild;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height= 1;
    newNode->left = newNode->right = NULL;
    newNode->leftChild = newNode->rightChild = 0;
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

    AVLNode* newParrent = pivotNode->left;
    pivotNode->left = newParrent->right;
    pivotNode->leftChild = newParrent->rightChild;
    newParrent->right = pivotNode;

    if (newParrent->right)
    {
        newParrent->rightChild = pivotNode->leftChild + pivotNode->rightChild + 1;
    }

    else
    {
        newParrent->rightChild = 0;
    }

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent = pivotNode->right;
    pivotNode->right = newParrent->left;
    pivotNode->rightChild = newParrent->leftChild;
    newParrent->left = pivotNode;

    if (newParrent->left)
    {
        newParrent->leftChild = pivotNode->leftChild + pivotNode->rightChild + 1;
    }

    else
    {
        newParrent->leftChild = 0;
    }

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
    
    if(node==NULL) // udah mencapai leaf
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value), node->leftChild++;
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value), node->rightChild++;
    
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

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value), node->rightChild--;
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value), node->leftChild--;
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->rightChild--;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

    if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor < -1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor < -1 && _getBalanceFactor(node->right)>0) 
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

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }
}

int findIndex(AVLNode *current, int value) 
{
    int index = 0;

    while(current != NULL)
    {
        if (value < current->data) 
        {
            current = current->left;
        }

        else if (value > current->data)
        {
            index += current->leftChild + 1, current = current->right;
        }
                
        else 
        {
            return (index + current->leftChild)%1000000007;
        }
    }

    return -1;
}

void permute(long long permutation[], int n)
{
    permutation[0] = 1;
    for (int i = prev; i < n; i++) 
    {
        factorial = (factorial * i)%1000000007;
        permutation[i] = factorial;
    }
    prev = n;
}

int main()
{
    int t;
    scanf("%d", &t);

    AVL avlku;
    long long permutation[100100] = {0};

    while (t--)
    {
        int n;
        long long sum = 0;
        scanf("%d", &n);

        int arr[n];
        avl_init(&avlku);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
            avl_insert(&avlku, arr[i]);
        }

        if (permutation[n-1] == 0)
        {
            permute(permutation, n);
        }
        
        for (int i = 0; i < n ; i++)
        {
            long long index = findIndex(avlku._root, arr[i]);
            index = (index*permutation[n-i-1])%1000000007;
            sum = (sum + index)%1000000007;
            avl_remove(&avlku, arr[i]);
        }

        printf("%lld\n", sum + 1);
    }

    return 0;
}