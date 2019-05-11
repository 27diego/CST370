#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

struct GraphNode{
    int data;
    vector<pair<GraphNode*, int>> neighbors;
    
public:
    GraphNode(int data)
    {
        this->data = data;
    }
};


struct Graph{
    vector<GraphNode*> nodes;
    
public:
    Graph(vector<GraphNode*> list)
    {
        this->nodes = list;
    }
};


unordered_map<GraphNode*, int> BellF(GraphNode* origin, Graph* g)
{
    auto distances =  unordered_map<GraphNode*, int>();
    for(auto nodes : g->nodes){distances[nodes] = INT_MAX;};
    distances[origin]=0;
    
    for(int x=0;x<g->nodes.size()-1;x++)
        for(auto node : g->nodes)
            for(auto neighbor:node->neighbors)
                if((distances[node]!=INT_MAX) &&(distances[neighbor.first]>distances[node]+neighbor.second))
                    distances[neighbor.first] = distances[node]+neighbor.second;
    
    return distances;
}




int main() {
    GraphNode *n0 = new GraphNode(0);
    GraphNode *n1 = new GraphNode(1);
    GraphNode *n2 = new GraphNode(2);
    GraphNode *n3 = new GraphNode(3);
    n0->neighbors.push_back(pair<GraphNode *, int>(n2, 8));
    n1->neighbors.push_back(pair<GraphNode *, int>(n2, 2));
    n1->neighbors.push_back(pair<GraphNode *, int>(n3, 6));
    n2->neighbors.push_back(pair<GraphNode *, int>(n0, 8));
    n2->neighbors.push_back(pair<GraphNode *, int>(n1, 2));
    n2->neighbors.push_back(pair<GraphNode *, int>(n3, 3));
    n3->neighbors.push_back(pair<GraphNode *, int>(n2, 3));
    vector<GraphNode *> nodes = {n0, n1, n2, n3};
    Graph* g = new Graph(nodes);
    
    auto ans = BellF(n0, g);
    for (auto p : ans)
        cout << p.first->data << ": " << p.second << endl;
}

/*
 2: 8
 1: 10
 3: 11
 0: 0
 */
