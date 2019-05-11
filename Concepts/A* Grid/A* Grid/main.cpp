#include <iostream>
#include <vector>
#include <map> // there's no hash function for pairs
#include <set> // there's no hash function for pairs
#include <climits>
using namespace std;

/*
 Manhattan distance heuristic.
 */
int manhattan(pair<int, int> curr, pair<int, int> goal) {
    return abs(curr.first - goal.first) + abs(curr.second - goal.second);
}

int heuristic(pair<int, int> curr, pair<int, int> goal) {
    return  manhattan(curr, goal);
}

/*
 Get the adjacent squares for the given square
 */
vector<pair<int, int>> get4(int x, int y, int maxX, int maxY)//(current.first,current.second,nodes.size(),nodes[0].size())
{
    vector<int> vx = {0, 0, 1, -1,-1,1,-1,1};
    vector<int> vy = {-1, 1, 0, 0,1,1,-1,-1};
    vector<pair<int, int>> ans = {};
    for (int i = 0; i < vx.size(); i++) {
        int nx = x + vx[i];
        int ny = y + vy[i];
        if ((nx >= 0) && (nx < maxX) && (ny >= 0) && (ny < maxY))
            ans.push_back(pair<int, int>(nx, ny));
    }
    return ans;
}

pair<int, int> mostPromisingAStarGrid(map<pair<int, int>, pair<int, int>> &distances, set<pair<int, int>> & finalized) {
    auto ans = pair<int, int>(-1, -1);
    int m = INT_MAX;
    for (auto p : distances) {
        auto node = p.first;
        int dist_to_node = p.second.first;
        int node_heuristic = p.second.second;
        if (!finalized.count(node) && dist_to_node + node_heuristic <= m) {
            m = dist_to_node + node_heuristic;
            ans = node;
        }
    }
    return ans;
}

// origin == source, dest(ination) == target
int AStarGrid(pair<int, int> origin, pair<int, int> dest, vector<vector<bool>> &nodes) {
    auto finalized = set<pair<int, int>>(); // 1 coordinates
    auto distances = map<pair<int, int>, pair<int, int>>(); // 2 <weight(g),heuristic>
    distances[origin] = pair<int, int>(0, heuristic(origin, dest)); // 3
    auto current = origin;
    //auto xy = origin; //a pair of x,y coordinates dedicated to 1 spot in the grid
    while ((current.first != dest.first || current.second != dest.second) &&(current.first != -1 && current.second != -1))//-1 out of bounds??
    { // 4
        finalized.insert(current); // 4a.
        for (auto p : get4(current.first, current.second, nodes.size(), nodes[0].size())) {// 4b. get4() is returning all 4 neighbors
            if (!finalized.count(p) && nodes[p.first][p.second])//while node is not finalized and it exists in the grid
            {
                if (!distances.count(p)) //if it doesnt exist on the distances map
                {
                    distances[p] = pair<int, int>(distances[current].first + 1, heuristic(p, dest));//+1 because of the # of steps you take
                } else if (distances[p].first > distances[current].first + 1) {
                    distances[p].first = distances[current].first + 1;
                }
            }
        }
        current = mostPromisingAStarGrid(distances, finalized); // 4c
    }
    return (current.first != -1 && current.second != -1 ? distances[dest].first : INT_MAX);
   // return distances[dest].first;
}

int main() {
    vector<vector<bool>> grid = {
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    
    cout << "ASTAR GRID: " << grid.size() <<"x"<< grid[0].size() << endl;
    cout << AStarGrid(pair<int, int>(0, 0), pair<int, int>(3, 3), grid)<<endl;
}
