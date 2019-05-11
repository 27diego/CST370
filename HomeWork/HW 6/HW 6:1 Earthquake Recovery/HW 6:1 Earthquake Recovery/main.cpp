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
    vector<pair<pair<GraphNode*, GraphNode*>, int>> list = {};
    for(auto node : nodes)
    {
        for(auto edge : node->neighbors)
        {
            list.push_back(pair<pair<GraphNode*, GraphNode*>, int>(pair<GraphNode*, GraphNode*>(node, edge.first), edge.second));
        }
    }
    return list;
}

bool sort_list(pair<pair<GraphNode*, GraphNode*>, int>first, pair<pair<GraphNode*, GraphNode*>, int>second)
{
    return first.second>second.second;
}

GraphNode* getRoot(GraphNode* current, unordered_map<GraphNode*, GraphNode*>list)
{
    while(list[current])
    {
        current = list[current];
    }
    return current;
}

vector<pair<pair<GraphNode*, GraphNode*>, int>>Kruskals(vector<GraphNode*>nodes)
{
    auto MST = vector<pair<pair<GraphNode*, GraphNode*>, int>>();
    auto edges = vector<pair<pair<GraphNode*, GraphNode*>, int>>();
    edges = getEdges(nodes);
    std::sort(edges.begin(), edges.end(), sort_list);
    
    auto roots = unordered_map<GraphNode*, GraphNode*>();
    
    while(MST.size()!=nodes.size()-1)
    {
        auto edge = edges[edges.size()-1];
        auto leftRoot = getRoot(edge.first.first, roots);
        auto rightRoot = getRoot(edge.first.second, roots);
        if(leftRoot!=rightRoot)
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
    for(auto node : reconnect)
    {
        result += node.second;
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
    
    
//    for(auto i : nodes)
//    {
//        for(auto starting : initial_dest)
//        {
//            if(starting == i->city)
//            {
//                start.push_back(i);
//            }
//        }
//    }
//
//    for(auto node : start)
//    {
//        cout<<node->city<<endl;
//    }
//
//    cout<<reconnection(Kruskals(start))<<endl;
    
}
