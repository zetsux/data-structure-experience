#include <bits/stdc++.h>
using namespace std;

void traverse(vector<pair<int,char>> adjList[], char arr[], int curVertex)
{
    if (adjList[curVertex].size() >= 1)
    {
        int nextVertex = adjList[curVertex][0].first;
        if (arr[nextVertex] == '.')
        {
            arr[curVertex] = '.';
            arr[nextVertex] = '*';
            traverse(adjList, arr, nextVertex);
        }

        else
        {
            return;
        }
    }

    else
    {
        return;
    }
}

int main ()
{
    int n;
    cin >> n;

    while (n--)
    {
        int x, y;
        cin >> x >> y;

        int cap = x*y;

        vector<pair<int,char>> adjList[cap];
        char arr[cap];

        for (int i = 0; i < cap; i++)
        {
            cin >> arr[i];
        }

        for (int i = 0; i < cap-y; i++)
        {
            adjList[i].push_back(make_pair((i+y), arr[i+y]));
        }

       for (int i = cap-y-1; i >= 0; i--)
        {
            if (arr[i] == '*')
            {
                traverse(adjList, arr, i);
            }
        }

        for (int i = 0; i < cap; i++)
        {
            cout << arr[i];
            if (i%y == y-1)
            {
                cout << endl;
            }
        }
    }

    return 0;
}