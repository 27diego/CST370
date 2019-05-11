Find Shortest Path
-
1. Create an empty set of finalized nodes.
2. Create map of nodes to pairs of distances (g, h). g is the distance so far, and h is the estimated distance to the goal using the heuristic.
3. Calculate the heuristic value for the origin h and set the distance for the origin to (0, h). Initialize a current node to the origin.f
4. While the current node is not the destination node:
    1. Add current node to the finalized set and Iterate over its neighbors:
    2. For each neighbor that is not finalized, update the g value (if less than the current g value, if it exists) to the sum of the “min dist” and the weight of the edge between it and the “min dist” node. Calculate the heuristic value for the neighbor and assign it to h.

    3. Set current to the “min dist” node – the node with the smallest f value that is not finalized where f = g + h.


Find most promising node in Distance table
-
1. set a holder for the answer node
2. make a comparison variable that updates when finding a new shorted distance when adding shortest path so far + heuristic valuae
3. iterate through the distance table
        1. make holder for node in table
        2. make holder for dist value in table
        3. make holder for heuristic value in table
        4. make boolean to see if the node has been finalized
        5. check if finalized and compare heuristic and path so far to comparison table that holds after each increment the smallest value
            1.if passes through if statement update the comparison value for next iterations
            2. update the answer node if there is lesser valued nodes available
4. once for loop terminates return answer node


Get the Neighbors
-
1. set the two lists representing the values to add the current coordinates to for checking the neighbors
2. set an empty holder list for the neighbors to add to
3. for the size of the potential neighbors
    1. set the x snd y coordinates to check for
    2. if the coordinates are in bounds
    3. add to the neighbors list
4. return the neighbors list
