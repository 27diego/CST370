#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

struct AMNode { //Floyd
    int data;
};


vector<vector<int>> floyd(vector<vector<int>> & edges) {//vector<AMNode *> &nodes) {
    auto dist = vector<vector<int>>(edges.size(), vector<int>(edges.size())); // initialize the answer
    // copy the adjacency matrix
    for (int i = 0; i < edges.size(); i++)
        for (int j = 0; j < edges.size(); j++)
            dist[i][j] = edges[i][j];
    // auto dist = edges;
    for (int k = 0; k < edges.size(); k++) // nodes to consider
        for (int j = 0; j < edges.size(); j++) // destination node
            for (int i = 0; i < edges.size(); i++) // source node
                // check there is a path from source to new node to consider
                // check there is a path from new node to consider to destination
                // check if sum of those paths is shorter than existing path
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    // update shortest path found from source to destination
                    dist[i][j] = dist[i][k] + dist[k][j];
    return dist;
}

int main() {
    vector<vector<int>> edges = {{0, INT_MAX, 8, INT_MAX}, {INT_MAX, 0, 2, 6}, {8, 2, 0, 3}, {INT_MAX, 6, 3, 0}};
    auto paths = floyd(edges);
    for (auto &v : paths) {
        for (int w : v)
            cout << w << " ";
        cout << endl;
    }
}
