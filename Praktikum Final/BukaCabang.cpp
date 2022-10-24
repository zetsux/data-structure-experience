#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

void dijkstra(vector<pii> v[], int n) 
{
    priority_queue <pii, vector <pii>, greater <pii>> pq;
    set <int> seen;
    int dist[n];
    memset(dist, -1, sizeof(dist));
    dist[0] = 0;
    pq.push({0, 0});
    while(!pq.empty()) 
    {
        pii now = pq.top();
        pq.pop();
        if (seen.find(now.second) != seen.end()) continue;
        seen.insert(now.second);
        for (long unsigned int i = 0; i < v[now.second].size(); i++) 
        {
            int next = v[now.second][i].second;
            int cost = v[now.second][i].first;

            if (now.first + cost < dist[next] || dist[next] == -1) 
            {
                dist[next] = now.first + cost;
                pq.push({dist[next], next});
            }
        }
    }

    for(int i = 1; i < n; i++) 
    {
        cout << i << " " << dist[i] << "\n";
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<pii> adjList[n];

    while (m--)
    {
        int a, b, w;
        cin >> a >> b >> w;

        adjList[a].push_back(make_pair(w,b));
        adjList[b].push_back(make_pair(w,a));
    }

    dijkstra(adjList, n);

    return 0;
}