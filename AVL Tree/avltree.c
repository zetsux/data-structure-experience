#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct TreeNode_t
{
    int data;
    struct TreeNode_t *left,*right;
    int height;
}TreeNode;

typedef struct Tree_t
{
    TreeNode *_root;
    unsigned int _size;
}Tree;

TreeNode* _createNode(int value) 
{
    TreeNode *new = (TreeNode*) malloc(sizeof(TreeNode));
    new->data = value;
    new->height = 1;
    new->left = new->right = NULL;
    return new;
}

TreeNode* _searchNode(TreeNode *root, int value) 
{
    while (root) 
    {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }

    return root;
}

int _getHeight(TreeNode* node)
{
    if(!node)
        return 0; 
    return node->height;
}

int _max(int a,int b)
{
    return (a > b)? a : b;
}

TreeNode* _rightRotate(TreeNode* pivot) 
{
    TreeNode* newParent = pivot->left;
    pivot->left = newParent->right;
    newParent->right = pivot;

    pivot->height = _max(_getHeight(pivot->left),
                      _getHeight(pivot->right))+1;
    newParent->height = _max(_getHeight(newParent->left),
                       _getHeight(newParent->right))+1;
    
    return newParent;
}

TreeNode* _leftRotate(TreeNode* pivot) 
{
    TreeNode* newParent = pivot->right;
    pivot->right = newParent->left;
    newParent->left = pivot;

    pivot->height=_max(_getHeight(pivot->left),
                      _getHeight(pivot->right))+1;
    newParent->height=_max(_getHeight(newParent->left),
                       _getHeight(newParent->right))+1;
    
    return newParent;
}

TreeNode* _leftCaseRotate(TreeNode* node)
{
    return _rightRotate(node);
}

TreeNode* _rightCaseRotate(TreeNode* node)
{
    return _leftRotate(node);
}

TreeNode* _leftRightCaseRotate(TreeNode* node)
{
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
}

TreeNode* _rightLeftCaseRotate(TreeNode* node)
{
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(TreeNode* node)
{
    if(!node)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

TreeNode* _insertNode(Tree *pohon, TreeNode* node, int value) 
{
    if(!node)
        return _createNode(value);
    if(value < node->data)
        node->left = _insertNode(pohon, node->left, value);
    else if(value > node->data)
    	node->right = _insertNode(pohon, node->right, value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

TreeNode* _findMinNode(TreeNode *node) 
{
    TreeNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

TreeNode* _removeNode(TreeNode* node, int value)
{
    if(!node)
        return node;
    if(value > node->data)
    	node->right = _removeNode(node->right, value);
    else if(value < node->data)
    	node->left = _removeNode(node->left, value);
    else
    {
        TreeNode *temp;
        if(!node->left || !node->right)
        {
            temp = NULL;
            if(!node->left) temp = node->right;  
            else if(!node->right) temp = node->left;
            
            if(!temp)
            {
                temp = node;
                node = NULL;
            }

            else
                *node = *temp;   
            
            free(temp);
        }

        else
        {
            temp = _findMinNode(node->right);
            node->data = temp->data;
            node->right = _removeNode(node->right,temp->data);
        }    
    }

	if(!node) return node;
    
    node->height =_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor = _getBalanceFactor(node);
    
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

void _inorder(TreeNode *root) 
{
    if (root) 
    {        
        _inorder(root->left);
        printf("%d ", root->data);
        _inorder(root->right);
    }
}

void init(Tree *pohon) 
{
    pohon->_root = NULL;
    pohon->_size = 0u;
}

bool isEmpty(Tree *pohon) 
{
    return pohon->_root == NULL;
}

bool find(Tree *pohon, int value) 
{
    TreeNode *temp = _searchNode(pohon->_root, value);
    if (!temp)
        return false;
    if (temp->data == value)
        return true;
    else
        return false;
}

void insert(Tree *pohon, int value)
{
    if(!find(pohon, value))
    {
        pohon->_root = _insertNode(pohon, pohon->_root, value);
        pohon->_size++;
        printf("Data %d berhasil dimasukkan ke dalam pohon!\n", value);
    }

    else
    {
        printf("Data %d sudah terdapat di dalam pohon!\n", value);
        return;
    }
}

void delete(Tree *pohon, int value)
{
    if(find(pohon, value))
    {
        pohon->_root = _removeNode(pohon->_root, value);
        pohon->_size--;
        printf("Data %d berhasil dihapuskan dari pohon!\n", value);
    }

    else
    {
        printf("Data %d tidak ditemukan di dalam pohon!\n", value);
        return;
    }
}

void clear(Tree *pohon)
{
    pohon->_root = NULL;
    pohon->_size = 0u;
    printf("Pohon telah dikosongkan!\n");
}

void inorder(Tree *pohon)
{
    printf("Isi pohon secara inorder : ");
    _inorder(pohon->_root);
    puts("");
}


int main()
{
    Tree pohon;
    init(&pohon);
    
    int i;
    for (i = 1 ; i <= 100 ; i++)
    {
    	insert(&pohon, i);
	}
    inorder(&pohon);
    
    for (i = 5 ; i <= 100 ; i += 5)
    {
    	delete(&pohon, i);
	}
    inorder(&pohon);
}
