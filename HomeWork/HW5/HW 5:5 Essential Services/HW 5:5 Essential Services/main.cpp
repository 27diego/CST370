#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

struct GraphNode{
    string name;
    vector<pair<GraphNode*,int>> neighbors;
    
public:
    GraphNode(string name)
    {
        this->name = name;
    }
};

struct Graph{
    vector<GraphNode*> nodes;
    
public:
    Graph(vector<GraphNode*>list)
    {
        this->nodes = list;
    }
};

GraphNode *minDist(unordered_map<GraphNode *, int> &distances, unordered_set<GraphNode *> & visited)
{
    GraphNode *ans = nullptr;
    int m = INT_MAX;
    for (auto p : distances)
        if (!visited.count(p.first) && p.second <= m) {
            m = p.second;
            ans = p.first;
        }
    return ans;
}


unordered_map<GraphNode*, int> services_path(GraphNode* origin, Graph* g)
{
    auto distances = unordered_map<GraphNode*, int>();
    auto finalized = unordered_set<GraphNode*>();
    
    for(auto nodes : g->nodes) {distances[nodes]=INT_MAX;}
    distances[origin] = 0;
    GraphNode* current = origin;
    
    while(finalized.size()!=g->nodes.size())
    {
        finalized.insert(current);
        for(auto neighbor : current->neighbors)
        {
            int edgeWeight = neighbor.second;
            int min_dist = distances[current];
            if(distances[neighbor.first]>edgeWeight+min_dist)
            {
                distances[neighbor.first] = edgeWeight+min_dist;
            }
        }
        
        current = minDist(distances, finalized);
    }
    
    return distances;
}


int services_path(GraphNode* origin, GraphNode* dest, Graph* g)
{
    auto distances = unordered_map<GraphNode*, int>();
    auto finalized = unordered_set<GraphNode*>();
    
    for(auto nodes : g->nodes) {distances[nodes]=INT_MAX;}
    distances[origin] = 0;
    GraphNode* current = origin;
    
    while(current!=dest && distances[current]!=INT_MAX)
    {
        finalized.insert(current);
        for(auto neighbor : current->neighbors)
        {
            int edgeWeight = neighbor.second;
            int min_dist = distances[current];
            if(distances[neighbor.first]>edgeWeight+min_dist)
            {
                distances[neighbor.first] = edgeWeight+min_dist;
            }
        }
        
        current = minDist(distances, finalized);
    }
    
    return distances[current];
}


int main()
{
    
    GraphNode *n0 = new GraphNode("Cersei");
    GraphNode *n1 = new GraphNode("Robert");
    GraphNode *n2 = new GraphNode("Jamie");
    GraphNode *n3 = new GraphNode("Qyburn");
    GraphNode *n4 = new GraphNode("Tomin");
    GraphNode *n5 = new GraphNode("Castle");
    GraphNode *n6 = new GraphNode("Church");
    
    vector<GraphNode*> elders{n0,n1,n2,n3,n4};
    vector<GraphNode*> services{n5,n6};
    
    n5->neighbors.push_back(pair<GraphNode *, int>(n1, 15));
    n1->neighbors.push_back(pair<GraphNode *, int>(n3, 155));
    n1->neighbors.push_back(pair<GraphNode *, int>(n4, 15));
    n5->neighbors.push_back(pair<GraphNode *, int>(n4, 35));
    n3->neighbors.push_back(pair<GraphNode *, int>(n6, 15));
    n1->neighbors.push_back(pair<GraphNode *, int>(n2, 30));
    n2->neighbors.push_back(pair<GraphNode *, int>(n6, 115));
    n1->neighbors.push_back(pair<GraphNode *, int>(n0, 300));
    n0->neighbors.push_back(pair<GraphNode *, int>(n6, 30));
    
    vector<GraphNode *> nodes = {n0, n1, n2, n3,n4,n5,n6};
    Graph* g = new Graph(nodes);
    
    cout<<"cersei->caster: "<<services_path(n4,n6, g)<<endl;
    cout<<"caster->cersei: "<<services_path(n6,n4, g)<<endl;
    
//    cout<<"from castle: "<<endl;
//    for(auto i:services_path(n5, g))
//    {
//        cout<<i.first->name<<":"<<i.second<<endl;
//    }
    

}

/*
 Castle Church
 220    60      Cersei
 45     115     Jamie
 170    15      Qyburn
 15     145     Robert
 30     160     Tomin
 */
