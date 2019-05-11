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

// Helper to get all the edges in the graph given all the nodes
// Each edge will appear twice but that's ok for this implementation of kruskals (it will automatically ignore duplicates)
vector<pair<pair<Node *, Node *>, int>> allEdges(vector<Node *> &nodes) {
    vector<pair<pair<Node*, Node*>, int>> answer = {};
    for(auto node : nodes)
    {
        for(auto edge : node->neighbors)
        {
            answer.push_back(pair<pair<Node*, Node*>, int>(pair<Node*, Node*>(node, edge.first), edge.second));
        }
    }
    return answer;
}

// Gets the "root" of the set a node in my MST is in
Node *rootNode(Node *curr, unordered_map<Node *, Node *> &sets) {
    Node* root = curr;
    while(sets[root])
    {
        root = sets[root];
    }
    return root;
}

// Compares edges based on weight (descending); used for sorting edges
bool edgeComp(pair<pair<Node *, Node*>, int> &left, pair<pair<Node *, Node*>, int> &right) {
    return left.second > right.second;
}

vector<pair<pair<Node *, Node*>, int>> kruskals(vector<Node *> &nodes) {
    auto edges = allEdges(nodes);
    sort(edges.begin(), edges.end(), edgeComp);
    vector<pair<pair<Node *, Node*>, int>> mst = {};
    unordered_map<Node *, Node *> sets = {};
    while(mst.size() < nodes.size() - 1) {
        auto edge = edges[edges.size() - 1];
        edges.pop_back();
        Node *lRoot = rootNode(edge.first.first, sets); // which subset is the origin in?
        Node *rRoot = rootNode(edge.first.second, sets); // which subset is the destination in?
        if (lRoot != rRoot) { // are these nodes in the same subset?if not, connect them!
            mst.push_back(edge);
            sets[lRoot] = rRoot;
        }
    }
    return mst;
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
    a->neighbors.push_back(pair<Node *, int>(g, 18));
    a->neighbors.push_back(pair<Node *, int>(f, 5));
    b->neighbors.push_back(pair<Node *, int>(a, 3));
    b->neighbors.push_back(pair<Node *, int>(e, 9));
    b->neighbors.push_back(pair<Node *, int>(d, 11));
    c->neighbors.push_back(pair<Node *, int>(g, 6));
    c->neighbors.push_back(pair<Node *, int>(d, 4));
    d->neighbors.push_back(pair<Node *, int>(g, 1));
    d->neighbors.push_back(pair<Node *, int>(b, 11));
    d->neighbors.push_back(pair<Node *, int>(c, 4));
    e->neighbors.push_back(pair<Node *, int>(g, 14));
    e->neighbors.push_back(pair<Node *, int>(b, 9));
    f->neighbors.push_back(pair<Node *, int>(a, 5));
    g->neighbors.push_back(pair<Node *, int>(a, 18));
    g->neighbors.push_back(pair<Node *, int>(c, 6));
    g->neighbors.push_back(pair<Node *, int>(d, 1));
    g->neighbors.push_back(pair<Node *, int>(e, 14));
    vector<Node *> nodes = {a, b, c, d, e, f, g};
    vector<pair<pair<Node *, Node *>, int>> kmst = kruskals(nodes);
    for (pair<pair<Node *, Node *>, int> &edge : kmst)
        cout << edge.first.first->data << " " << edge.first.second->data << " " << edge.second << endl;
}


/*
 g d 1
 a b 3
 d c 4
 a f 5
 e b 9
 b d 11
 */
