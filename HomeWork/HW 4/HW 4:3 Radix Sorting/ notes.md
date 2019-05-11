Building
-
1. Find the maximum in the array.
2. Iterate over the digits, from least significant (1s) to most significant (found using the maximum value in the array).
    a. In each iteration, sort the array into buckets between 0 and 9, considering only the current digit.
    b. Concatenate the buckets in order and repeat( add them to an output list and repeat the recursion with this list) 




