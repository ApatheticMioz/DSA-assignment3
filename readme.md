# **Data Structures Assignment 3**

## Thought Process
  I used AVL Trees instead of plain BSTs because I needed searching to be at worst-case to be ``O(logn)``, and that can only be achieved with AVL trees (as per knowledge in DS-Course).
  The layout specified in the assignment for each structure was kept, following the diagram for the 3 node classes.

  Time complexities discussed are simplified to their base forms. (Average)

## Overview

### 1. Insertion: 
  Handles data insertion for players and games, checking for primary key conflicts.

  The relevant text files are opened, and then read line by line, comma by comma, into different variables from which nodes are created.
  Time complexity for loading Player Tree is ``O(n)``. 
  Time complexity for loading Game Tree is ``O(n)``.
  
### 2. Search and Retrieval: 
  Finds entries based on primary keys.

  Searching is simple, implemented recursively with a time complexity of ``O(log(n))``.
  
### 3. Deletion: 
  Deletes entries from the tree, ensuring no memory leaks.

  Deletion is done by following the algorithms defined for deletion in an AVL tree.
  Height calculations, rotations, balancing, deletion of BST, combined to make a delete function for AVL trees.

  Time complexity is ``O(log(n))``.
  
### 4. Save Data: 
  Exports data from the tree back to a CSV file using Preorder Traversal.

  Data is written to respective .csv files using Pre-order Traversal which results in a time complexity of ``O(n)`` for both trees writing.

  Reading the data is done efficiently by first building an array of the file, which is a sorted array, and then recursion is used to build the right and left subtrees
  knowing that the root is at the middle of the array.

  Time complexity is ``O(n)``. 
  Linear for reading file, building array, and transforming array into an AVL tree recursively. 
  
### 5. Show N Layers: 
  Displays nodes up to a specified tree depth.

  In-order traversal is used, keeping track of layers visited.

  Time complexity is ``O(n)``. 
  As the worst case traverses an entire tree.
  
### 6. Show Layer Number: 
  Returns the tree layer of a specific node.

  The node is found using a simple iterative search, found in ``O(log(n))`` time.
  
### 7. Show Path:
  Prints the Preorder Traversal path to a specified entry.

  While the node is not found, pre-order traversal is printed. This is done in ``O(log(n))`` time.
  
### 8. Edit Entry: 
  Allows editing of a player or game entry, with repositioning if the primary key changes.

  First, the node is searched and deleted, done in ``O(log(n))`` time,
  then the new node is inserted, done in ``O(log(n))`` time.

  Overall time complexity is ``O(log(n))``.
  
### 9. Top N Players: 
  Retrieves players with the highest number of associated games.

  This functionality was not implemented.
  
### 10. Show Details: 
  Lists the details of a player along with their played games.

  The node is found in ``O(log(n))`` time and then the details are printed, nothing special. 
  
### 11. Has Played: 
  Confirms if a specific player has played a given game with a time complexity of at most 2 log(n).

  The time complexity requirement was achieved by using AVL trees, which eliminates the worst case scenario search of ``O(n^2)`` in a skewed-BST.
  An AVL tree will remain balanced, which always improves the searching/inserting etc time complexities to ``O(log(n))``.

  The result is at most ``O(2 log(n))`` because first the Player AVL tree is searched, and then the inner GamesPlayed AVL tree is searched.
  ``O(log(n))`` + ``O(log(n))`` = ``O(2 log(n))``.
  Hence, desired time complexity is achieved.
  
