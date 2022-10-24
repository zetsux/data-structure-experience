#include <bits/stdc++.h>
using namespace std;

set<int> check;

void dfs(vector<int> adjList[], bool visited[], int curVertex)
{
    if (!check.count(curVertex))
    {
        check.insert(curVertex);
    }
    visited[curVertex] = 1;
    for (long unsigned int i = 0 ; i < adjList[curVertex].size() ; i++)
    {
        int nextVertex = adjList[curVertex][i];
        if (!visited[nextVertex])
        {
            dfs(adjList, visited, nextVertex);
        }
    }
}

int main ()
{
    int v, n, count = 0, num = 1;
    cin >> v >> n;

    vector<int> adjList[v+1];
    bool visited[v+1] = {0};
    set<int> safe;

    while (n--)
    {
        int a, b;
        cin >> a >> b;

        adjList[a].push_back(b);
        adjList[b].push_back(a);
        if (!safe.count(a))
        {
            safe.insert(a);
        }

        if (!safe.count(b))
        {
            safe.insert(b);
        }
    }

    while(num <= v)
    {
        if (safe.count(num))
        {
            if (!check.count(num))
            {
                dfs(adjList, visited, num);
                for (int i = 0 ; i <= v ; i++)
                {
                    visited[i] = 0;
                }

                count++;
            }
        }

        else
        {
            count++;
        }

        num++;
    }

    cout << count - 1 << endl;
    return 0;
}