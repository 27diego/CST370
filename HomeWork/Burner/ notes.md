Look-up
-
1. Set `current` to be the root of the trie.
2. For each letter in the word, move current to the pointer for that letter in the current node.
3. If a null pointer is encountered, return false immediately.
4. When the end of the word is reached, return the value of leaf for the current node.

Insert
-
1. Set `current` to the root of the trie.
2. For each letter in the word, move current to the pointer for that letter in the current node.
3. If a null pointer is encountered, create a new node with leaf set to false and set the pointer for that letter to the new node.
4. When the end of the word is reached, toggle leaf on the current node to true.

Delete
-
1. Set `current` to the root of the trie.
2. For each letter in the word, move current to the pointer for that letter in the current node.
3. If a null pointer is encountered, return (the word was already not in the trie).
4. When the end of the word is reached, toggle leaf on the current node to false.
5. Retracing the path backwards, while the current node is not a leaf and has no children, delete the current node.


