#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;


struct Edge 
{
    int to;
    int weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

class Graph 
{
public:
    int numVertices;  
    vector<vector<Edge>> adjList;  

    Graph(int vertices) 
{
        numVertices = vertices;
        adjList.resize(vertices);
    }

    void addEdge(int u, int v, int weight = 1) 
{
        adjList[u].push_back(Edge(v, weight));
        adjList[v].push_back(Edge(u, weight));  // 无向图
    }

    void displayGraph() 
{
        cout << "Graph adjacency list:\n";
        for (int i = 0; i < numVertices; i++) 
        {
            cout << "Vertex " << i << ": ";
            for (auto &edge : adjList[i]) 
            {
                cout << "(" << edge.to << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

// BFS 算法
void BFS(Graph &graph, int start) 
{
    vector<bool> visited(graph.numVertices, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";
    while (!q.empty()) 
    {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        for (auto &neighbor : graph.adjList[curr]) 
        {
            if (!visited[neighbor.to]) 
            {
                visited[neighbor.to] = true;
                q.push(neighbor.to);
            }
        }
    }
    cout << endl;
}

// DFS 算法
void DFSUtil(Graph &graph, int node, vector<bool> &visited) 
{
    visited[node] = true;
    cout << node << " ";
    for (auto &neighbor : graph.adjList[node]) 
    {
        if (!visited[neighbor.to]) 
        {
            DFSUtil(graph, neighbor.to, visited);
        }
    }
}

void DFS(Graph &graph, int start) 
{
    vector<bool> visited(graph.numVertices, false);
    cout << "DFS Traversal: ";
    DFSUtil(graph, start, visited);
    cout << endl;
}

// Dijkstra 算法
void Dijkstra(Graph &graph, int start) 
{
    vector<int> dist(graph.numVertices, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) 
    {
        int distance = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (distance > dist[curr]) continue;

        for (auto &neighbor : graph.adjList[curr]) 
        {
            int newDist = distance + neighbor.weight;
            if (newDist < dist[neighbor.to]) 
            {
                dist[neighbor.to] = newDist;
                pq.push({newDist, neighbor.to});
            }
        }
    }

    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < graph.numVertices; i++) 
    {
        cout << "Node " << i << ": " << dist[i] << endl;
    }
}

// Prim 算法
void Prim(Graph &graph) 
{
    vector<int> key(graph.numVertices, INT_MAX);
    vector<bool> inMST(graph.numVertices, false);
    vector<int> parent(graph.numVertices, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) 
    {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto &neighbor : graph.adjList[u]) 
        {
            int v = neighbor.to;
            int weight = neighbor.weight;

            if (!inMST[v] && weight < key[v]) 
            {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    cout << "Edges in MST:\n";
    for (int i = 1; i < graph.numVertices; i++) 
    {
        cout << parent[i] << " - " << i << endl;
    }
}
