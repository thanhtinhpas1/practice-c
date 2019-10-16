#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef PCH_H
#define PCH_H

typedef struct bst_node_t {
	int value;
	struct bst_node_t *left;
	struct bst_node_t *right;
}bst_node;

// insert the given value
bst_node* insert(bst_node *node, const int value);

// outputs the vlaues stored in the tree
void print_tree(bst_node *node);

// returns the number of nodes
int get_node_count(bst_node *node);

// delete all nodes in tree
void delete_tree(bst_node *node);

// Returns true if given value is in the tree
bool is_in_tree(bst_node *node, int value);

// Returns the height of the tree in nodes, 0 if empty
int get_height(bst_node* node);

// Returns the greater of 2 values
int max_num(int, int);

// Returns the minimum value in the tree, 0 if empty
int get_min(bst_node* node);

// Returns the maximum value in the tree, 0 if empty
int get_max(bst_node* node);

// Returns true if given node is root of a binary search tree
bool is_binary_search_tree(bst_node* node);

// Returns true if the node's value is between a min and max
bool is_between(bst_node* node, int min, int max);

// Deletes the given value from the tree
bst_node* delete_value(bst_node* node, int value);

// Returns the node containing the minimum value in the tree rooted by the given
// node.

// Returns next-highest value in tree after given value, -1 if none
int get_successor(bst_node* node, int value);

#endif //PCH_H
