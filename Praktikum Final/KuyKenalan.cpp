#include <bits/stdc++.h>
using namespace std;

long long inf = std::numeric_limits<long long>::max();

struct AVLTree {
    struct AVLTree* left;
    struct AVLTree* right;
    long long key;
    struct AVLTree* par;
    long long height;
    long long stats;
};

long long counter = 0;
list<long long> passed;
vector<long long> tempSafe[1000000];

void Updateheight(struct AVLTree* root)
{
    if (root != NULL) 
    {
        long long val = 1;

        if (root->left != NULL)
            val = root->left->height + 1;
 
        if (root->right != NULL)
            val = max(
                val, root->right->height + 1);

        root->height = val;
    }
}
 
struct AVLTree* LLR(struct AVLTree* root)
{
    struct AVLTree* tmpnode = root->left;
    root->left = tmpnode->right;

    if (tmpnode->right != NULL)
        tmpnode->right->par = root;
 
    tmpnode->right = root;
    tmpnode->par = root->par;
    root->par = tmpnode;

    if (tmpnode->par != NULL && root->key < tmpnode->par->key) 
    {
        tmpnode->par->left = tmpnode;
    }

    else 
    {
        if (tmpnode->par != NULL)
            tmpnode->par->right = tmpnode;
    }
 
    root = tmpnode;

    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);
 
    return root;
}
 
struct AVLTree* RRR(struct AVLTree* root)
{
    struct AVLTree* tmpnode = root->right;

    root->right = tmpnode->left;
 
    if (tmpnode->left != NULL)
        tmpnode->left->par = root;
 
    tmpnode->left = root;
    tmpnode->par = root->par;
    root->par = tmpnode;

    if (tmpnode->par != NULL && root->key < tmpnode->par->key) 
    {
        tmpnode->par->left = tmpnode;
    }

    else 
    {
        if (tmpnode->par != NULL)
            tmpnode->par->right = tmpnode;
    }
 
    root = tmpnode;
 
    Updateheight(root->left);
    Updateheight(root->right);
    Updateheight(root);
    Updateheight(root->par);
 
    return root;
}
 
struct AVLTree* LRR(struct AVLTree* root)
{
    root->left = RRR(root->left);
    return LLR(root);
}

struct AVLTree* RLR(struct AVLTree* root)
{
    root->right = LLR(root->right);
    return RRR(root);
}

struct AVLTree* Balance(struct AVLTree* root)
{
    long long firstheight = 0;
    long long secondheight = 0;
 
    if (root->left != NULL)
        firstheight = root->left->height;
 
    if (root->right != NULL)
        secondheight = root->right->height;
 
    if (abs(firstheight - secondheight) == 2) 
    {
        if (firstheight < secondheight) 
        {
            long long rightheight1 = 0;
            long long rightheight2 = 0;
            if (root->right->right != NULL)
                rightheight2 = root->right->right->height;
 
            if (root->right->left != NULL)
                rightheight1 = root->right->left->height;
 
            if (rightheight1 > rightheight2) 
            {
                root = RLR(root);
            }
            else 
            {
                root = RRR(root);
            }
        }

        else 
        {
            long long leftheight1 = 0;
            long long leftheight2 = 0;
            if (root->left->right != NULL)
                leftheight2 = root->left->right->height;
 
            if (root->left->left != NULL)
                leftheight1 = root->left->left->height;
 
            if (leftheight1 > leftheight2) 
            {
                root = LLR(root);
            }

            else 
            {
                root = LRR(root);
            }
        }
    }
 
    return root;
}
 
struct AVLTree* Insert(struct AVLTree* root, struct AVLTree* parent, long long key)
{
    if (root == NULL) 
    {
        root = new struct AVLTree;
 
        if (root != NULL)
        {
            root->height = 1;
            root->left = NULL;
            root->right = NULL;
            root->par = parent;
            root->key = key;
        }
    }
 
    else if (root->key > key) 
    {
        root->left = Insert(root->left, root, key);

        long long firstheight = 0;
        long long secondheight = 0;
 
        if (root->left != NULL)
            firstheight = root->left->height;
 
        if (root->right != NULL)
            secondheight = root->right->height;
 
        if (abs(firstheight - secondheight) == 2) 
        {
            if (root->left != NULL && key < root->left->key) 
            {
                root = LLR(root);
            }

            else 
            {
                root = LRR(root);
            }
        }
    }
 
    else if (root->key < key) 
    {
        root->right = Insert(root->right,
                             root, key);

        long long firstheight = 0;
        long long secondheight = 0;
 
        if (root->left != NULL)
            firstheight
                = root->left->height;
 
        if (root->right != NULL)
            secondheight = root->right->height;
 
        if (abs(firstheight - secondheight) == 2) 
        {
            if (root->right != NULL && key < root->right->key)
            {
 
                root = RLR(root);
            }

            else 
            {
                root = RRR(root);
            }
        }
    }

    Updateheight(root);
    return root;
}

bool Search(struct AVLTree* root, long long key)
{
    if (root == NULL)
        return false;
 
    else if (root->key == key)
        return true;
 
    else if (root->key > key) 
    {
        bool val = Search(root->left, key);
        return val;
    }

    else 
    {
        bool val = Search(root->right, key);
        return val;
    }
}

struct AVLTree* Delete(struct AVLTree* root, long long key)
{
    if (root != NULL)
    {
        if (root->key == key) 
        {
            if (root->right == NULL && root->left != NULL) 
            {
                if (root->par != NULL) 
                {
                    if (root->par->key
                        < root->key)
                        root->par->right = root->left;
                    else
                        root->par->left = root->left;
 
                    Updateheight(root->par);
                }
 
                root->left->par = root->par;
 
                root->left = Balance(
                    root->left);
 
                return root->left;
            }
 
            else if (root->left == NULL && root->right != NULL) 
            {
                if (root->par != NULL) 
                {
                    if (root->par->key
                        < root->key)
                        root->par->right = root->right;
                    else
                        root->par->left = root->right;
 
                    Updateheight(root->par);
                }
 
                root->right->par = root->par;

                root->right = Balance(root->right);
                return root->right;
            }
 
            else if (root->left == NULL && root->right == NULL) 
            {
                if (root->par->key < root->key) 
                {
                    root->par->right = NULL;
                }

                else 
                {
                    root->par->left = NULL;
                }
 
                if (root->par != NULL)
                    Updateheight(root->par);
 
                root = NULL;
                return NULL;
            }

            else {
                struct AVLTree* tmpnode = root;
                tmpnode = tmpnode->right;
                while (tmpnode->left != NULL) {
                    tmpnode = tmpnode->left;
                }
 
                long long val = tmpnode->key;
 
                root->right
                    = Delete(root->right, tmpnode->key);
 
                root->key = val;
                root = Balance(root);
            }
        }
 
        else if (root->key < key) 
        {
            root->right = Delete(root->right, key);
            root = Balance(root);
        }
 
        else if (root->key > key) 
        {
            root->left = Delete(root->left, key);
            root = Balance(root);
        }
 
        if (root != NULL) 
        {
            Updateheight(root);
        }
    }
 
    return root;
}

struct AVLTree* Find(struct AVLTree* root, long long key)
{
    while (root != NULL) 
    {
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root;
    }

    return root;
}

void Expansion(struct AVLTree* root, bool visited[], long long dist, long long maxDist, long long maxCount)
{
    if (root == NULL || dist > maxDist || visited[root->key])
    {
        return;
    }

    visited[root->key] = true;
    tempSafe[dist].push_back(root->key);
    counter++;
    if (counter >= maxCount)
    {
        return;
    }

    if (root->par != NULL)
    {
        if (root->par->key < root->key)
        {
            Expansion(root->right, visited, dist + 1, maxDist, maxCount);
            Expansion(root->left, visited, dist + 1, maxDist, maxCount);
            Expansion(root->par, visited, dist + 1, maxDist, maxCount);
        }

        else
        {
            Expansion(root->par, visited, dist + 1, maxDist, maxCount);
            Expansion(root->right, visited, dist + 1, maxDist, maxCount);
            Expansion(root->left, visited, dist + 1, maxDist, maxCount);
        }
    }

    else
    {
        Expansion(root->right, visited, dist + 1, maxDist, maxCount);
        Expansion(root->left, visited, dist + 1, maxDist, maxCount);
    }
}

void Expand(struct AVLTree* root, long long key, long long maxDist, long unsigned int maxCount)
{
    struct AVLTree* temp = Find(root, key);
    bool visited[1000000] = {0};
    counter = 0;
    Expansion(temp, visited, 0, maxDist, maxCount);

    for (long long i = 0; i <= maxDist; i++)
    {
        sort(tempSafe[i].begin(), tempSafe[i].end());
        while (!tempSafe[i].empty())
        {
            if (passed.size() < maxCount)
            {
                passed.push_back(tempSafe[i].back());
            }
            tempSafe[i].pop_back();
        }
    }
            
    passed.sort();
    passed.unique();

    while (!passed.empty()) 
    {
        cout << passed.back() << " ";
        passed.pop_back();
    }
    cout << endl;
}
 
int main()
{
    struct AVLTree* root;
    root = NULL;

    long long com;
    cin >> com;

    while (com != -1)
    {
        if (com == 0)
        {
            long long start, dist, count;
            cin >> start >> dist >> count;

            if (root == NULL || !Search(root, start))
            {
                cout << "Eyyy lom dateng :)\n";
            }

            else
            {
                if (count == -1)
                {
                    count = inf;
                }
                Expand(root, start, dist, count);
            }
        }

        else
        {
            while (com--)
            {
                long long in;
                cin >> in;

                root = Insert(root, NULL, in);
            }
        }

        cin >> com;
    }
    
    cout << "End";
    return 0;
}