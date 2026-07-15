#include <iostream>
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

    bool isCyclic(int u, std::vector<bool>& isVisited, std::vector<bool>& isRecursionPath){
        isVisited[u] = true;
        isRecursionPath[u] = true;

        for(int neighbor : adj[u]){
            if(!isVisited[neighbor]){
                if(isCyclic(neighbor, isVisited, isRecursionPath)){
                    return true;
                }
            }else
                if(isRecursionPath[neighbor]){
                    return true;
                }
            
        }
        isRecursionPath[u] = false;
        return false;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,1);
    g.addEdge(3,4);


    std::vector<bool> isVisited(5,false);
    std::vector<bool> isRecursionPath(5,false);
    bool isCycle{false};
    for(int i = 0; i<5; i++){
        if(!isVisited[i]){
            isCycle = g.isCyclic(i,isVisited, isRecursionPath);
        }
        if(isCycle){
            std::cout<<"This is a cyclic graph";
            break;
        }
    }
    if(!isCycle){
        std::cout<<"This is a non cyclic graph";
    }
    return 0;
}
