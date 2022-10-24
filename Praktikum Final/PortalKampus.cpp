#include <bits/stdc++.h>
using namespace std;

unsigned long long inf = numeric_limits<int>::max();
typedef pair<unsigned long long, pair<int, long long>> pulii;
vector<long long> dist;

void dijkstra(vector<pulii> v[], int s, int n) 
{
    priority_queue <pulii, vector<pulii>, greater<pulii>> pq;
    set<int> seen;
    dist.assign(n+1, -1);
    dist[s] = 0;
    pq.push({0, {s, 1}});
    while(!pq.empty()) 
    {
        pulii now = pq.top();
        pq.pop();
        if(seen.find(now.second.first) != seen.end()) continue;
        seen.insert(now.second.first);
        for(long unsigned int i = 0; i < v[now.second.first].size(); i++) 
        {
            int next = v[now.second.first][i].first;
            long long card = v[now.second.first][i].second.first;
            long long cost = v[now.second.first][i].second.second + (abs(card - now.second.second));
            if (next == n - 1)
            {
                cost += (abs(card - 1));
                card = 1;
            }

            if(now.first + cost < dist[next] || dist[next] == inf) 
            {
                dist[next] = now.first + cost;
                if (next != n-1)
                {
                    pq.push({dist[next], {next, card}});
                }
            }
        }
    }

    cout << dist[n-1];
    return;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<pulii> adjList[n + 1];

    while (m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        adjList[a].push_back(make_pair(b, make_pair(c, d)));
        adjList[b].push_back(make_pair(a, make_pair(c, d)));
    }

    dijkstra(adjList, 1, n + 1);
    return 0;
}