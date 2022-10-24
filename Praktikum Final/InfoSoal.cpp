#include <bits/stdc++.h>
using namespace std;

int flag = 0;

void dfs(list<int> adjList[], vector<bool> visited, int curVertex, int count, int v)
{
    visited[curVertex] = 1;

    if (count == v)
    {
        flag = 1;
    }

    if (flag) 
    {
        return;
    }

    for (auto i = adjList[curVertex].begin(); i != adjList[curVertex].end(); ++i)
    {
        int nextVertex = *i;
        if (!visited[nextVertex])
        {
            dfs(adjList, visited, nextVertex, count + 1, v);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 

    int v, e;
    cin >> v >> e;

    vector<int> adjList[v];
    vector<bool> visited;
    for (int i = 0; i <= v ; i++)
    {
        visited.push_back(0);
    }

    while (e--)
    {
        int a, b;
        cin >> a >> b;

        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    list<int> jumpadjList[v];

    for (int i = 0; i < v ; i++)
    {
        for (long unsigned int k = 0 ; k < adjList[i].size() ; k++)
        {
            int nextVertex = adjList[i][k];
            for (long unsigned int j = 0 ; j < adjList[nextVertex].size() ; j++)
            {
                int jumpVertex = adjList[nextVertex][j];
                jumpadjList[i].push_back(jumpVertex);
            }
        }

        jumpadjList[i].sort();
        jumpadjList[i].unique();
    }

    for (int i = 0; i < v ; i++)
    {
        dfs(jumpadjList, visited, i, 1, v);
        if (flag)
        {
            cout << "YES";
            return 0;
        }
    }

    cout << "NO";
    return 0;
}