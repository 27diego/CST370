Kruskal's Algorithm
-
1. Initialize an empty minimum spanning tree (set of edges).
2. Initialize a vector of edges. Find and sort all edges in graph by weight.
3. Initialize a map of nodes to nodes. Start with all nodes in the graph mapped to itself.
4. While the size of the MST is less than the number of nodes – 1, repeat:
    1. Pick the smallest remaining edge.
    2. If it does not form a cycle with the previously selected edges (roots are different), add it to the MST and map the root of one neighbor to the root of the other.
    3. Remove it from the edges vector.
4. Return the MST.

Union Find
-
1. Given a map of nodes to nodes and an edge in a graph:
2. Look up the “from” node in the given map to find that node’s “root”. (from_root)
3. Look up the “to” node in the given map to find that node’s “root”. (to_root)
4. Return the value of from_root == to_root.


1. Given a map of nodes to nodes and an edge in a graph:
2. Look up the “from” node in the given map to find that node’s “root”. (from_root)
3. Look up the “to” node in the given map to find that node’s “root”. (to_root)
4. Update to_root’s value in the map to be equal to from_root
