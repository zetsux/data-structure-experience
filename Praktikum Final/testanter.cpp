#include <bits/stdc++.h>
using namespace std;

set<int> all;
long long minimum = numeric_limits<int>::max();

void dfs(int curVertex, vector<pair<int,int>> adj[], list<int> target, vector<bool> visited, long long total, int count)
{
    if (all.size() == count)
    {
        minimum = min(minimum, total);
        return;
    }

    visited[curVertex] = 1;
    if (curVertex == target.front())
    {
        target.pop_front();
    }

    for (int i = 0 ; i < adj[curVertex].size() ; i++)
    {
        int nextVertex = adj[curVertex][i].first;
        if (!visited[nextVertex])
        {
            if (target.front() != nextVertex)
            {
                if (!all.count(nextVertex))
                {
                    dfs(nextVertex, adj, target, visited, total + adj[curVertex][i].second, count);
                }
            }

            else
            {
                dfs(nextVertex, adj, target, visited, total + adj[curVertex][i].second, count + 1);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  

    int n, m, d;
    cin >> n >> m >> d;

    vector<pair<int,int>> adjList[n];
    while (m--)
    {
        int a, b, c;
        cin >> a >> b >> c;

        adjList[a].push_back(make_pair(b,c));
        adjList[b].push_back(make_pair(a,c));
    }

    list<int> target;
    int first = -1;
    while (d--)
    {
        int t;
        cin >> t;

        all.insert(t);
        if (first == -1)
        {
            first = t;
        }
        
        else
        {
            target.push_back(t);
        }
    }

    vector<bool> visited;
    for (int i = 0; i < n ; i++)
    {
        visited.push_back(0);
    }

    dfs(first, adjList, target, visited, 0, 1);
    cout << "res: " << minimum;
    return 0;
}