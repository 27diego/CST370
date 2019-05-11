1. Initialize a map of nodes to distances, dist. 
2. Set distance to the origin node = 0 and to every other node = max_int/infinity. O(1)
3. Iterate over number of vertices minus 1 (k, the potential max number of edges on our shortest paths): O(V)
    1. Iterate over all the edges, (u,v) : O(E)
        a. If dist[u] is infinity, skip it: we cannot reach that vertex yet.
        b. If there is a shorter path to v through u, update the distance in dist[v]: (i.e., dist[v] > dist[u] + weight(u,v))
    2. If no distances were updated, exit early and return the distance map: O(1)
4. Iterate over all the edges again. If a distance was updated, there is a negative
cycle. O(1)
5. Return the distance map.
