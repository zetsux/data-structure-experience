#include <bits/stdc++.h>
using namespace std;

class Graph 
{
    int V;
    list<int>* adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs);
    void topologicalSortUtil(int v, bool visited[], stack<int>& Stack);
 
public:
    Graph(int V);
    void addEdge(int v, int w);
    bool isCyclic();
    void topologicalSort();
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        visited[v] = true;
        recStack[v] = true;
 
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
 
    }
    recStack[v] = false;
    return false;
}

bool Graph::isCyclic()
{
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 1; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
 
    for (int i = 1; i < V; i++)
        if ( !visited[i] && isCyclicUtil(i, visited, recStack))
            return true;
 
    return false;
}
 
void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);
    Stack.push(v);
}
 
void Graph::topologicalSort()
{
    stack<int> Stack;
    bool* visited = new bool[V];
    for (int i = 1; i < V; i++)
        visited[i] = false;
 
    for (int i = 1; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);
 
    while (Stack.empty() == false) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}
 
int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n + 1);

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }

    if (g.isCyclic())
    {
        cout << "-1";
        return 0;
    }

    g.topologicalSort();
    return 0;
}