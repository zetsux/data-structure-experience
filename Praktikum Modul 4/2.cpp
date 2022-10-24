#include <bits/stdc++.h>
using namespace std;
#define N 3
 
struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int miss;
    int level;
};

struct comparisonObj
{
    bool operator()(const Node* left, const Node* right)
    {
        return (left->miss + left->level) > (right->miss + right->level);
    }
};

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };
int correct[N][N];

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << mat[i][j];
        }

        cout << "\n";
    }
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
 
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
 
    node->miss = INT_MAX;
    node->level = level;

    node->x = newX;
    node->y = newY;
 
    return node;
}
 
int countMiss(int board[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (board[i][j] && board[i][j] != correct[i][j])
           count++;
    return count;
}
 
int isValid(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root)
{
    if (root->parent == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    int flag = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (root->mat[i][j] != correct[i][j])
            {
                flag = 0;
                break;
            }
        }
    }

    if (flag == 0)
    {
        cout << "\n";
    }
}
 
void puzzleSolve(int board[N][N], int x, int y)
{
    priority_queue<Node*, vector<Node*>, comparisonObj> myPq;
 
    Node* root = newNode(board, x, y, x, y, 0, NULL);
    root->miss = countMiss(board);

    myPq.push(root);

    while (!myPq.empty())
    {
        Node* min = myPq.top();
        myPq.pop();
 
        if (min->miss == 0)
        {
            cout << "Langkah minimum = " << min->level << endl;
            printPath(min);
            return;
        }
 
        for (int i = 0; i < 4; i++)
        {
            if (isValid(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                child->miss = countMiss(child->mat);
                myPq.push(child);
            }
        }
    }
}

int countInverse (int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
             if (arr[j] && arr[i] && arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}

bool checkImpossible (int puzzle[3][3])
{
    int count = countInverse((int *)puzzle);
    return (count%2 == 0);
}
 
int main()
{
    string line;
    while (getline(cin, line))
    {
        string puzzle;
        for (int i = 0; i < 3 ; i++)
        {
            puzzle += line;
            getline(cin, line);
        }

        int board[N][N];
        int x = -1, y = -1;
        for (int i = 0; i < 3 ; i++)
        {
            for (int j = 0; j < 3 ; j++)
            {
                board[i][j] = puzzle[(i*3)+j] - 48;
                correct[i][j] = (i*3)+j+1;

                if (board[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
            }
        }

        correct[2][2] = 0;

        if (!checkImpossible(board))
        {
            cout << "Kerjain dl aja kerjaannya\n";
            continue;
        }

        puzzleSolve(board, x, y);
    }
}
