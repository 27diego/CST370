#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct GraphNode{
    string name;
    vector<pair<GraphNode*, int>> neighbors;
    
public:
    GraphNode(string name)
    {
        this->name = name;
    }
};

struct Graph{
    vector<GraphNode*> nodes;
    
    Graph(vector<GraphNode*> list)
    {
        this->nodes = list;
    }
};


unordered_map<GraphNode*, int> BellF(GraphNode* source, Graph* g)
{
    auto distances = unordered_map<GraphNode*, int>();
    for(auto node:g->nodes){distances[node]=INT_MAX;}
    distances[source] = 0;
    
    for(int x=0;x<g->nodes.size()-1;x++)
        for(auto node : g->nodes)
            for(auto neighbor : node->neighbors)
            {
                if((distances[node]!=INT_MAX) && (distances[neighbor.first]>neighbor.second+distances[node]))
                    distances[neighbor.first] = neighbor.second + distances[node];
                
    
    return distances;
}


bool compare(string a, string b)
{
    return a<b;
}

int main()
{
 
    GraphNode *n0 = new GraphNode("Bookworks");
    GraphNode *n1 = new GraphNode("Home");
    GraphNode *n2 = new GraphNode("Beach");
    GraphNode *n3 = new GraphNode("Aquarium");
    GraphNode *n4 = new GraphNode("Starbucks");
    GraphNode *n5 = new GraphNode("Carmel");
    n0->neighbors.push_back(pair<GraphNode *, int>(n1, 95));
    n0->neighbors.push_back(pair<GraphNode *, int>(n3, -50));
    n1->neighbors.push_back(pair<GraphNode *, int>(n3, 150));
    n1->neighbors.push_back(pair<GraphNode *, int>(n4, 12));
    n1->neighbors.push_back(pair<GraphNode *, int>(n2, -100));
    n2->neighbors.push_back(pair<GraphNode *, int>(n4, 55));
    n3->neighbors.push_back(pair<GraphNode *, int>(n0, 50));
    n4->neighbors.push_back(pair<GraphNode *, int>(n5, 200));
    n5->neighbors.push_back(pair<GraphNode *, int>(n1, -100));
    
    vector<GraphNode *> nodes = {n0, n1, n2, n3,n4,n5};
    Graph* g = new Graph(nodes);
    
    auto ans = BellF(n1, g);
    
    auto sorted = vector<string>();
    for(auto i : ans)
    {
        sorted.push_back(i.first->name);
    }
    
    std::sort(sorted.begin(), sorted.end(), compare);
    
    auto fin = vector<pair<string, int>>();
    
    for (auto i : sorted)
    {
        for(auto x : ans )
        {
            if(i == x.first->name)
            {
                fin.push_back(pair<string, int>(i,x.second));
            }
        }
    }
    
    for(auto i : fin)
    {
         cout << i.first << ": " << i.second << endl;
    }
    
}
    
    /*
     Bookworks: 200
     Home: 0
     Aquarium: 150
     Starbucks: -45
     Beach: -100
     Carmel: 155
     */
