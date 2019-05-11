#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

struct GraphNode {
    int data; // whatever data it holds
    vector<pair<GraphNode *, int> > neighbors;//pairs of neighbor nodes and their weights
public:
    GraphNode(int d)//constructor initializing a new node with some data and no neighbors
    {
        data = d;
        neighbors = {};
    }
};

struct Graph //whole graph containing all nodes
{
    vector<GraphNode*> nodes;
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

void print_table(unordered_map<GraphNode*, int> distances)
{
    for(auto dist : distances)
    {
        cout<<dist.first->data<<":"<<dist.second<<endl;
    }
}

int dijkstras(GraphNode* origin, GraphNode* dest, Graph* g)
{
    auto distances = unordered_map<GraphNode*, int>();
    auto finalized = unordered_set<GraphNode*>();
    
    for(auto nodes : g->nodes) {distances[nodes]=INT_MAX;}
    distances[origin] = 0;
    GraphNode* current = origin;
    
    while(current!=dest&&distances[current]!=INT_MAX)
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




int heuristic(GraphNode* curr, GraphNode* target) {
    // SOMETHING RELATED TO THE DATA
    return 0;
}

GraphNode* mostPromisingAStar(unordered_map<GraphNode *, pair<int, int>> &distances, unordered_set<GraphNode *> & finalized)
{
    GraphNode* answer = nullptr;
    int comparison_value = INT_MAX;
    
    for(auto distance : distances)
    {
        GraphNode* node = distance.first;
        int shortest_path = distance.second.first;
        int heuristic_value = distance.second.second;
        bool isFinalized = finalized.count(node)==1;
        
        if(!isFinalized && shortest_path+heuristic_value<comparison_value)
        {
            comparison_value = shortest_path+heuristic_value;
            answer = node;
        }
    }
    return answer;
}

int astar(GraphNode* origin, GraphNode* dest, Graph* g)
{
    auto finalized = unordered_set<GraphNode*>();
    auto distances = unordered_map<GraphNode*, pair<int, int>>();
    
    distances[origin] = pair<int,int>(0, heuristic(origin, dest));
    
    GraphNode* current = origin;
    
    while(current!=dest)
    {
        finalized.insert(current);
        
        for(auto neighbor : current->neighbors)
        {
            int min_dist = distances[current].first;
            int edge_weight = neighbor.second;
            if(distances.count(neighbor.first))
            {
                int node_distance = distances[neighbor.first].first;
                if(min_dist+edge_weight<node_distance)
                {
                    distances[neighbor.first] = pair<int, int>(min_dist+ edge_weight, heuristic(neighbor.first, dest));
                }
                
            }
            else
            {
                distances[neighbor.first] = pair<int,int>(min_dist+ edge_weight, heuristic(neighbor.first, dest));
            }
        }
        current = mostPromisingAStar(distances, finalized);
    }
    return distances[current].first;
}




int main() {
    
    GraphNode *n0 = new GraphNode(0);
    GraphNode *n1 = new GraphNode(1);
    GraphNode *n2 = new GraphNode(2);
    GraphNode *n3 = new GraphNode(3);
    GraphNode *n4 = new GraphNode(4);
    GraphNode *n5 = new GraphNode(5);
    GraphNode *n6 = new GraphNode(6);
    GraphNode *n7 = new GraphNode(7);
    GraphNode *n8 = new GraphNode(8);
    GraphNode *n9 = new GraphNode(9);
    n0->neighbors = {{n1, 1}, {n2, 2}, {n3, 8}};
    n1->neighbors = {{n0, 1}, {n4, 4}, {n3, 3}};
    n2->neighbors = {{n0, 2}, {n4, 1}, {n5, 3}, {n9, 10}};
    n3->neighbors = {{n0, 8}, {n1, 3}, {n7, 5}};
    n4->neighbors = {{n1, 4}, {n2, 1}, {n9, 5}};
    n5->neighbors = {{n2, 3}, {n6, 6}};
    n6->neighbors = {{n5, 6}};
    n7->neighbors = {{n3, 5}, {n8, 2}};
    n8->neighbors = {{n7, 2}, {n9, 1}};
    n9->neighbors = {{n2, 10}, {n4, 5}, {n8, 1}};
    vector<GraphNode *> graph = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9};
    Graph* g = new Graph();
    g->nodes = graph;
//    print_table(dijkstras(n0, g));
//    cout<<"------------------"<<endl;
//    print_table(dijkstras(n4, g));
    cout << dijkstras(n0, n6, g) << endl;
    cout << dijkstras(n4, n0, g) << endl;
    cout << "ASTAR" << endl;
    
    cout << astar(n0, n6, g) << endl;
    cout << astar(n4, n0, g) << endl;
}
