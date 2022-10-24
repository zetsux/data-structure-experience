#include <bits/stdc++.h>
using namespace std;

int done = 0;
void dfs(vector<int> adjList[], bool visited[], int curVertex, int v)
{
    if(curVertex == v)
    {
        done = 1;
        return;
    }

    visited[curVertex] = 1;
    int nextVertex = adjList[curVertex][0];
    if (nextVertex != -1)
    {
        if (!visited[nextVertex])
        {
            dfs(adjList, visited, nextVertex, v);
        }
    }

    if (!done)
    {
        nextVertex = adjList[curVertex][1];
        if (nextVertex != -1)
        {
            if (!visited[nextVertex])
            {
                dfs(adjList, visited, nextVertex, v);
            }
        }
    }
}

int main()
{
    int n, m, count = 0;
    cin >> n >> m;

    string board[n];
    for (int i = 0; i < n; i++)
    {
        cin >> board[i];
    }

    vector<int> adj[n*m];
    bool visited[n*m] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] != '#')
            {
                if (j < m-1 && board[i][j+1] != '#')
                {
                    adj[(i*m)+j].push_back((i*m)+j+1);
                }

                else
                {
                    adj[(i*m)+j].push_back(-1);
                }

                if (i < n-1 && board[i+1][j] != '#')
                {
                    adj[(i*m)+j].push_back((i*m)+j+m);
                }

                else
                {
                    adj[(i*m)+j].push_back(-1);
                }
            }

            else
            {
                adj[(i*m)+j].push_back(-1);
                adj[(i*m)+j].push_back(-1);
            }
        }
    }

    if (m != 1)
    {
        dfs(adj, visited, 1, (n*m)-1);
    }

    if (done == 1)
    {
        count++;
        done = 0;
    }

    if (n != 1)
    {
        dfs(adj, visited, m, (n*m)-1);
    }
    
    if (done == 1)
    {
        count++;
    }

    cout << count;
    return 0;
}