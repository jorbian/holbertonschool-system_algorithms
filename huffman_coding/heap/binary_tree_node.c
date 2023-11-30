#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

/**
 * binary_tree_node - creates a generic Binary Tree node
 * @parent: pointer to the parent node of node beiong created
 * @data: data to be stored in the node
 *
 * Return: pointer to the created node or NULL if it fails
*/
node_t *binary_tree_node(node_t *parent, void *data)
{
	node_t *new_node;

	new_node = malloc(sizeof(node_t));
	if (new_node == NULL)
		return (NULL);

	new_node->data = data;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
