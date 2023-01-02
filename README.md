# BST-Project
This is a program that implements a binary search tree for storing products. A binary search tree is a type of data structure that stores data in a hierarchical manner, where nodes in the tree contain data that is less than or greater than the data in its parent node. This allows for fast insertion, deletion, and searching of data in the tree.

The program defines a node structure that stores a product's stock keeping unit (SKU), name, price, and pointers to its left and right children in the tree. The createNode function creates a new node with the given SKU, name, and price, and initializes its left and right pointers to NULL.

The addProduct function takes a pointer to the root node of the tree, a SKU, a name, and a price, and adds a new node to the tree with the given data. If the tree is empty, it creates a new root node with the given data. Otherwise, it compares the SKU of the new node to the SKU of the root node and adds the new node to the left or right child of the root node accordingly, so that the tree remains in sorted order.

The findProduct function searches the tree for a node with a given SKU and returns a pointer to the node if found, or NULL if not found. It does this by comparing the SKU of the root node to the target SKU, and if the target SKU is less than or equal to the root node's SKU, it searches the left child of the root node. If the target SKU is greater than the root node's SKU, it searches the right child of the root node.

The minValueNode function returns a pointer to the node with the smallest SKU in the tree. It does this by starting at the root node and following the left child of each node until it reaches a leaf node.

The deleteProduct function removes a node with a given SKU from the tree. If the tree is empty, it returns NULL. If the target SKU is less than the root node's SKU, it searches the left child of the root node. If the target SKU is greater than the root node's SKU, it searches the right child of the root node. If the target node is found, it is removed from the tree using one of several techniques, depending on whether the node has zero, one, or two children.

The minCoins function is an implementation of the dynamic programming algorithm for finding the minimum number of coins needed to make a given value. It takes an array of coin denominations, the number of coins in the array, and the target value as inputs, and returns the minimum number of coins needed to make the target value. It does this by considering all possible combinations of coin denominations and selecting the combination that requires the fewest number of coins.

The showProductList function prints a list of all the products in the tree, in sorted order by SKU. It does this by traversing the tree in-order (left child, root, right child).

The totalCartValue function returns the total cost of all the products in the tree. It does this by traversing the tree and adding the price of each product to a running total.

The readProductInfo function reads product data from a file and adds each product to the tree using the addProduct function.

The main function prompts the user to perform various actions on the tree, such as adding a product, deleting a product, or displaying the list of products
