#include <bits/stdc++.h>
using namespace std;

int flag = 0;

void traverse(vector< pair<int,int> > adjList[], bool visited[], int arr[], int curVertex)
{
    visited[curVertex] = 1;
    for (long unsigned int i = 0 ; i < adjList[curVertex].size() ; i++)
    {
        int nextVertex = adjList[curVertex][i].first;

        if (!visited[nextVertex])
        {
            if (arr[nextVertex] == 0)
            {
                traverse(adjList, visited, arr, nextVertex);
            }

            else if (arr[nextVertex] == 3)
            {
                flag = 1;
                return;
            }
        }
    }
}

int main ()
{
    int n, start = -1;
    cin >> n;
    vector< pair<int,int> > adjList[n*n];
    bool visited[n*n] = {0};

    int arr[n*n];

    for (int i = 0; i < n*n; i++)
    {
        cin >> arr[i];
        if (arr[i] == 2)
        {
            start = i;
        }
}

    for (int i = 0; i < n*n; i++)
    {
        if (i >= n)
        {
            adjList[i].push_back(make_pair((i-n), arr[i-n]));
            adjList[i - n].push_back(make_pair((i), arr[i]));
        }

        if (i < (n*n)-n)
        {
            adjList[i].push_back(make_pair((i+n), arr[i+n]));
            adjList[i + n].push_back(make_pair((i), arr[i]));
        }

        if (i%n > 0)
        {
            adjList[i].push_back(make_pair(i - 1, arr[i - 1]));
            adjList[i - 1].push_back(make_pair(i, arr[i]));
        }

        if (i%n < n-1)
        {
            adjList[i].push_back(make_pair(i + 1, arr[i + 1]));
            adjList[i + 1].push_back(make_pair(i, arr[i]));
        }
    }

    traverse(adjList, visited, arr, start);

    if (flag == 1)
    {
        cout << "yey";
    }

    else
    {
        cout << "yah";
    }

    return 0;
}
