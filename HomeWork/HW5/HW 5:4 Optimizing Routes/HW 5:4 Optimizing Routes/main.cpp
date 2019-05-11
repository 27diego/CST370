#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
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
    
public:
    Graph(vector<GraphNode*> list)
    {
        this->nodes = list;
    }
};

unordered_map<GraphNode*, int> BellF(Graph* graph, GraphNode* origin)
{
    auto finalized = unordered_set<GraphNode*>();
    auto distances = unordered_map<GraphNode*, int>();
    for(auto i : graph->nodes){distances[i]=INT_MAX;}
    distances[origin]=0;
    auto current = origin;
    
    for(int x=0;x<graph->nodes.size()-1;x++)
        for(auto node : graph->nodes)
            for(auto neighbor : node->neighbors)
                if((distances[node]!=INT_MAX) && (distances[neighbor.first]>neighbor.second+distances[node]))
                {
                    distances[neighbor.first]=neighbor.second+distances[node];
                }

    return distances;
}

bool compare(pair<string, string>a, pair<string, string>b)
{
    transform(a.first.begin(), a.first.end(), a.first.begin(), ::tolower);
    transform(b.first.begin(), b.first.end(), b.first.begin(), ::tolower);
    return a.first<b.first;
}


int main()
{
    
    //nodes : , , , 17 - Mile Drive
    GraphNode *home = new GraphNode("Home");
    GraphNode *bookworks = new GraphNode("Bookworks");
    GraphNode *csumb = new GraphNode("CSUMB");
    GraphNode *east_village = new GraphNode("East Village");
    GraphNode *carmel_beach = new GraphNode("Carmel Beach");
    GraphNode *presidio = new GraphNode("Presidio");
    GraphNode *rei = new GraphNode("REI");
    GraphNode *colton_hall = new GraphNode("Colton Hall");
    GraphNode *sushi = new GraphNode("Sushi Time");
    GraphNode *aquarium = new GraphNode("Aquarium");
    GraphNode *mile_drive = new GraphNode("17 - Mile Drive");
    GraphNode *carmel_village = new GraphNode("Carmel Village");
    
    auto initial_dest = unordered_map<string, int>();
    initial_dest.insert(pair<string, int>("Bookworks",9));
    initial_dest.insert(pair<string, int>("CSUMB",16));
    initial_dest.insert(pair<string, int>("East Village",6));
    initial_dest.insert(pair<string, int>("Carmel Beach",21));
    
    presidio->neighbors.push_back(pair<GraphNode *, int>(bookworks, 3));
    presidio->neighbors.push_back(pair<GraphNode *, int>(aquarium, 3));
    presidio->neighbors.push_back(pair<GraphNode *, int>(colton_hall, 2));
    presidio->neighbors.push_back(pair<GraphNode *, int>(home, 5));
    
    home->neighbors.push_back(pair<GraphNode *, int>(carmel_village, 17));
    home->neighbors.push_back(pair<GraphNode *, int>(rei, 12));
    home->neighbors.push_back(pair<GraphNode *, int>(carmel_village, 17));
    home->neighbors.push_back(pair<GraphNode *, int>(csumb, 16));
    home->neighbors.push_back(pair<GraphNode *, int>(east_village, 6));
    home->neighbors.push_back(pair<GraphNode *, int>(mile_drive, 10));
    home->neighbors.push_back(pair<GraphNode *, int>(colton_hall, 4));
    home->neighbors.push_back(pair<GraphNode *, int>(sushi, 10));
    rei->neighbors.push_back(pair<GraphNode *, int>(csumb, 3));
    csumb->neighbors.push_back(pair<GraphNode *, int>(sushi, 7));
    carmel_beach->neighbors.push_back(pair<GraphNode *, int>(mile_drive, 12));
    east_village->neighbors.push_back(pair<GraphNode *, int>(colton_hall, 5));
    colton_hall->neighbors.push_back(pair<GraphNode *, int>(home, 4));
    carmel_village->neighbors.push_back(pair<GraphNode *, int>(carmel_beach, 4));
    
    vector<GraphNode *> nodes = {home, bookworks, csumb, east_village, carmel_beach, presidio, rei, colton_hall, sushi, aquarium, mile_drive, carmel_village};
    Graph* g = new Graph(nodes);
    
    auto results = BellF(g, home);
    
    auto printing = vector<pair<string, string>>();
    
    for(auto initial : initial_dest)
    {
        for(auto result : results)
        {
            if(initial.first==result.first->name)
            {
                if(initial.second == result.second)
                {
                    printing.push_back(pair<string, string>(initial.first,"Fastest"));
                }
                else if(initial.second>result.second)
                {
                    printing.push_back(pair<string, string>(initial.first, to_string(initial.second-result.second)));
                }
                else
                {
                    printing.push_back(pair<string, string>(initial.first, "NO PATH"));
                }
            }
        }
    }
    
    std::sort(printing.begin(), printing.end(), compare);
    
    cout<<"----"<<endl;
    for(auto i : printing)
    {
        cout<<i.first << " : "<<i.second<<endl;
    }
}

/*
 Bookworks NO PATH
 Carmel Beach FASTEST
 CSUMB 1
 East Village FASTEST
 */
