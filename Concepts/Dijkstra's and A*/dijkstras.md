1. Create an empty set of finalized nodes.
2. Create map of nodes to distances.  Initialize every node to map to infinity.
3. Set the distance for the origin to 0. Initialize a current node to the origin.
4. While the current node is not the destination and it’s distance is not infinity.foi
    1. Add the current node to the finalized set.
    2. Iterate over its neighbors:
    3. For each neighbor that is not finalized, update its distance (if less than its current distance) to the sum of the “min dist” and the weight of the edge between it and the “min dist” node.
    4. Set the current node to the “min dist” node – the node with the smallest distance that is not finalized. 
5. Return the value for the destination from the map.

