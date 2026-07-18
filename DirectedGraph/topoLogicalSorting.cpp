#include <iostream>
#include <stack>
#include <vector>

class Graph
{
    std::vector<std::vector<int>> adj;

public:
    Graph(int n) : adj(n) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int u, std::vector<bool>& visited, std::stack<int>& s){
        visited[u] = true;
        for(int neighbor : adj[u]){
            if(!visited[neighbor]){
                dfs(neighbor, visited,s);
            }
        }
        s.push(u);
    }

    void topoSort(){
        std::vector<bool> visited(adj.size(), false);
        std::stack<int> s;
        for(int i = 0; i<adj.size(); i++){
            if(!visited[i]){
                dfs(i,visited, s);
            }
        }

        while(!s.empty()){
            std::cout<<s.top()<<" ";
            s.pop();
        }

    }

    
};

int main(){
    Graph g(6);
    g.addEdge(5,0);
    g.addEdge(4,0);
    g.addEdge(4,1);
    g.addEdge(5,2);
    g.addEdge(2,3);
    g.addEdge(3, 1);

    g.topoSort();

}
