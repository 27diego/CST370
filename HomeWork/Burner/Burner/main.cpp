#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct GraphNode{
    string city;
    vector<pair<GraphNode*, int>> neighbors;
    
public:
    GraphNode(string name)
    {
        this->city = name;
    }
};

vector<pair<pair<GraphNode*, GraphNode*>, int>> getEdges(vector<GraphNode*> nodes)
{
//    vector<pair<pair<GraphNode*, GraphNode*>, int>> edges = {};
    auto edges = vector<pair<pair<GraphNode*, GraphNode*>, int>>();
    for(auto i : nodes)
    {
        for(auto neighbor : i->neighbors)
        {
            edges.push_back(pair<pair<GraphNode*, GraphNode*>, int>(pair<GraphNode*, GraphNode*>(i, neighbor.first),neighbor.second));
        }
    }
    return edges;
}

bool sort_list(pair<pair<GraphNode*, GraphNode*>, int>first, pair<pair<GraphNode*, GraphNode*>, int>second)
{
    return first.second > second.second;
}

GraphNode* getRoot(GraphNode* current, unordered_map<GraphNode*, GraphNode*>list)
{
    while(list.count(current))
    {
        current = list[current];
    }
    return current;
}

vector<pair<pair<GraphNode*, GraphNode*>, int>>Kruskals(vector<GraphNode*>nodes)
{
    /*
     1. Initialize an empty minimum spanning tree (set of edges).
     2. Initialize a vector of edges. Find and sort all edges in graph by weight.
     3. Initialize a map of nodes to nodes. Start with all nodes in the graph mapped to itself.
     4. While the size of the MST is less than the number of nodes – 1, repeat:
     1. Pick the smallest remaining edge.
     2. If it does not form a cycle with the previously selected edges (roots are different), add it to the MST and map the root of one neighbor to the root of the other.
     3. Remove it from the edges vector.
     4. Return the MST.
     */
    
    auto MST = vector<pair<pair<GraphNode*, GraphNode*>, int>>();
    auto edges = vector<pair<pair<GraphNode*, GraphNode*>, int>>();
    
    edges = getEdges(nodes);
    std::sort(edges.begin(), edges.end(), sort_list);
    
    auto roots = unordered_map<GraphNode*, GraphNode*>();
    
    while(MST.size()!=nodes.size()-1)
    {
        auto edge = edges[edges.size()-1];
        auto leftEdge = getRoot(edge.first.first, roots);
        auto rightEdge = getRoot(edge.first.second, roots);
        
        if(leftEdge != rightEdge)
        {
            MST.push_back(edge);
            roots[edge.first.first] = edge.first.second;
        }
        edges.pop_back();
    }
    return MST;
}


int reconnection(vector<pair<pair<GraphNode*, GraphNode*>, int>> reconnect)
{
    int result = 0;
    for(auto i : reconnect)
    {
        result += i.second;
    }
    
    return result;
}


int main()
{
    GraphNode* pacific = new GraphNode("Pacific Grove");
    GraphNode* salinas = new GraphNode("Salinas");
    GraphNode* monterey = new GraphNode("Monterey");
    GraphNode* seaside = new GraphNode("Seaside");
    GraphNode* marina = new GraphNode("Marina");
    GraphNode* csumb = new GraphNode("CSUMB");
    GraphNode* pebble = new GraphNode("Pebble Beach");
    
    vector<string> initial_dest = {"Pacific Grove","Salinas", "Monterey", "Seaside", "Marina", "CSUMB", "Pebble Beach"};
    
    pacific->neighbors.push_back(pair<GraphNode*, int>(monterey, 80));
    pacific->neighbors.push_back(pair<GraphNode*, int>(pebble, 10));
    pacific->neighbors.push_back(pair<GraphNode*, int>(csumb, 20));
    monterey->neighbors.push_back(pair<GraphNode*, int>(marina, 15));
    monterey->neighbors.push_back(pair<GraphNode*, int>(salinas, 30));
    marina->neighbors.push_back(pair<GraphNode*, int>(salinas, 45));
    seaside->neighbors.push_back(pair<GraphNode*, int>(csumb, 25));
    seaside->neighbors.push_back(pair<GraphNode*, int>(marina, 15));
    csumb->neighbors.push_back(pair<GraphNode*, int>(marina, 10));
    
    vector<GraphNode*> nodes = {pacific, salinas, monterey, seaside, marina, csumb, pebble};
    
    vector<GraphNode*> start;
    
    cout<<reconnection(Kruskals(nodes))<<endl;
}
