#include <bits/stdc++.h>
using namespace std;
 
void find_paths(vector<vector<int>> &paths, vector<int> &path, vector<int> parent[], int n, int node)
{
    if (node == -1) 
    {
        paths.push_back(path);
        return;
    }

    for (long unsigned int i = 0; i < parent[node].size(); i++)
    {
        int par = parent[node][i];
        path.push_back(node);
        find_paths(paths, path, parent, n, par);
        path.pop_back();
    }
}

void bfs(vector<int> adj[], vector<int> parent[], int n, int startNode)
{
    vector<int> level(n, INT_MAX);
    queue<int> q;
    q.push(startNode);
    level[startNode] = 0;
    while (!q.empty())
    {
        int curNode = q.front();
        q.pop();
        for (long unsigned int i = 0 ; i < adj[curNode].size() ; i++)
        {
            int nextNode = adj[curNode][i];
            if (level[nextNode] > level[curNode] + 1) 
            {
                level[nextNode] = level[curNode] + 1;
                q.push(nextNode);
                parent[nextNode].clear();
                parent[nextNode].push_back(curNode);
            }

            else if (level[nextNode] == level[curNode] + 1)
            {
                parent[nextNode].push_back(curNode);
            }
        }
    }
}
 
void simulateCounter(vector<int> adj[], int n, int startNode, int endNode, long double passCount[])
{
    vector<vector<int>> paths;
    vector<int> path;
    vector<int> parent[n];
    parent[startNode] = { -1 };

    bfs(adj, parent, n, startNode);
    find_paths(paths, path, parent, n, endNode);

    long double pathCount = paths.size();
 
    for (long unsigned int i = 0 ; i < paths.size(); i++) 
    {
        auto v = paths[i];
        reverse(v.begin(), v.end());

        for (long unsigned int j = 0 ; j < v.size() ; j++)
        {
            passCount[v[j]]++;
        }
    }

    passCount[startNode] = passCount[endNode] = pathCount;
    for (int k = 1; k < n; k++)
    {
        passCount[k] = 2.0*((long double)passCount[k]/(long double)pathCount);
        cout << fixed << setprecision(9) << passCount[k] << endl;
    }
}
 
int main()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    n++;
    vector<int> adj[n];

    while (m--)
    {
        int x, y, w;
        cin >> x >> y >> w;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    long double passCount[n] = {0};
    simulateCounter(adj, n, a, b, passCount);
 
    return 0;
}