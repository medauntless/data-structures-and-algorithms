#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph
{
    vector<vector<int>> adj;

public:
    Graph(int v) : adj(v) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void displayGraph() const
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            cout << i << " : ";
            for (int neigh : adj[i])
            {
                cout << neigh << " ";
            }
            cout << "\n";
        }
    }

    void bfs(int u)
    {
        queue<int> q;
        vector<bool> visited(adj.size(), false);

        q.push(u);
        visited[u] = true;

        while (!q.empty())
        {
            int val = q.front();
            q.pop();

            cout << val << "\t";

            for (int neigh : adj[val])
            {
                if (!visited[neigh])
                {
                    q.push(neigh);
                    visited[neigh] = true;
                }
            }
        }

        cout << "\n";
    }

    void dfsHelper(int u, vector<bool> &visited)
    {
        cout << u << "\t";
        visited[u] = true;

        for (int neigh : adj[u])
        {
            if (!visited[neigh])
            {
                dfsHelper(neigh, visited);
            }
        }
    }

    void dfs(int u)
    {
        vector<bool> visited(adj.size(), false);
        dfsHelper(u, visited);
        cout << "\n";
    }

    bool isCyclicDfsHelper(int u, vector<bool> &visited, int parent)
    {
        visited[u] = true;

        for (int neigh : adj[u])
        {
            if (!visited[neigh])
            {
                if (isCyclicDfsHelper(neigh, visited, u))
                {
                    return true;
                }
            }
            else if (neigh != parent)
            {
                return true;
            }
        }

        return false;
    }

    bool isCyclicDfs()
    {
        vector<bool> visited(adj.size(), false);

        for (size_t i = 0; i < adj.size(); i++)
        {
            if (!visited[i])
            {
                if (isCyclicDfsHelper(i, visited, -1))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool isCyclicBfs()
    {
        vector<bool> visited(adj.size(), false);

        for (size_t i = 0; i < adj.size(); i++)
        {
            if (visited[i])
                continue;

            queue<pair<int, int>> q;
            q.push({static_cast<int>(i), -1});
            visited[i] = true;

            while (!q.empty())
            {
                int val = q.front().first;
                int parent = q.front().second;
                q.pop();

                for (int neigh : adj[val])
                {
                    if (!visited[neigh])
                    {
                        q.push({neigh, val});
                        visited[neigh] = true;
                    }
                    else if (neigh != parent)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

int main()
{
    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 5);

    g.displayGraph();

    g.bfs(4);
    g.bfs(2);

    g.dfs(0);
    g.dfs(4);

    cout << g.isCyclicDfs() << "\n";
    cout << g.isCyclicBfs() << "\n";

    return 0;
}
