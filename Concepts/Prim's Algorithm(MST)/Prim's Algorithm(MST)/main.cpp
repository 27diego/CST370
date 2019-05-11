#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string data;
    vector<pair<Node *, int>> neighbors;
public:
    Node(string d) {
        data = d;
    }
};


Node *minNode(unordered_map<Node *, pair<Node *, int>> &dist) {
    int mDist = INT_MAX;
    Node *mNode = nullptr;
    for (auto p : dist)
        if (p.second.second <= mDist) {
            mDist = p.second.second;
            mNode = p.first;
        }
    return mNode;
}

vector<pair<pair<Node *, Node*>, int>> prims(vector<Node *> &nodes) {
    auto ans = vector<pair<pair<Node *, Node*>, int>>();
    // initializes vector of pairs - this is the mst we will be returning
    auto dist = unordered_map<Node *, pair<Node *, int>>();
    // initializes map to keep track of distance of nodes from the mst
    for (Node *node : nodes)
        // add all the nodes to the map
        dist[node] = pair<Node *, int>(nullptr, INT_MAX);
    // start out with no edge connecting them to the mst because the mst is empty
    for (int i = 0; i < nodes.size(); i++) {
        // iterate over number of nodes because that is how many nodes will be in the mst
        Node *mNode = minNode(dist);
        // gets min node - the node with the smallest weight between it and ANY node in the mst
        if (dist[mNode].first != nullptr) {
            // checks this isn't the first node we picked
            auto p = pair<Node *, Node*>(mNode, dist[mNode].first);
            // creates the edge (pair of nodes) that connects the min node to the mst
            ans.push_back(pair<pair<Node *, Node*>, int>(p, dist[mNode].second));
            // adds the edge and its weight to the mst
        }
        dist.erase(mNode);
        // removes min node from map because we already chose it (already in the mst)
        for (auto neighbor : mNode->neighbors) {
            // iterate over the min node's neighbors to update shortest edges connecting remaining nodes to mst
            if (dist.count(neighbor.first) && neighbor.second < dist[neighbor.first].second)
                // compares weight of the edge to the min node to the weight of the edge we stored (connects the neighbor to some other node in the mst)
                dist[neighbor.first] = pair<Node *, int>(mNode, neighbor.second);
            // update value for neighbor to be the edge connecting it to the mst
        }
    }
    return ans;
}



int main() {
    Node *a = new Node("a");
    Node *b = new Node("b");
    Node *c = new Node("c");
    Node *d = new Node("d");
    Node *e = new Node("e");
    Node *f = new Node("f");
    Node *g = new Node("g");
    a->neighbors.push_back(pair<Node *, int>(b, 3));
    b->neighbors.push_back(pair<Node *, int>(a, 3));
    a->neighbors.push_back(pair<Node *, int>(g, 18));
    g->neighbors.push_back(pair<Node *, int>(a, 18));
    a->neighbors.push_back(pair<Node *, int>(f, 5));
    f->neighbors.push_back(pair<Node *, int>(a, 5));
    g->neighbors.push_back(pair<Node *, int>(c, 6));
    c->neighbors.push_back(pair<Node *, int>(g, 6));
    g->neighbors.push_back(pair<Node *, int>(d, 1));
    d->neighbors.push_back(pair<Node *, int>(g, 1));
    g->neighbors.push_back(pair<Node *, int>(e, 14));
    e->neighbors.push_back(pair<Node *, int>(g, 14));
    b->neighbors.push_back(pair<Node *, int>(e, 9));
    e->neighbors.push_back(pair<Node *, int>(b, 9));
    b->neighbors.push_back(pair<Node *, int>(d, 11));
    d->neighbors.push_back(pair<Node *, int>(b, 11));
    c->neighbors.push_back(pair<Node *, int>(d, 4));
    d->neighbors.push_back(pair<Node *, int>(c, 4));
    vector<Node *> nodes = {a, b, c, d, e, f, g};
    vector<pair<pair<Node *, Node *>, int>> pmst = prims(nodes);
    for (pair<pair<Node *, Node *>, int> &edge : pmst)
        cout << edge.first.first->data << " " << edge.first.second->data << " " << edge.second << endl;
}
