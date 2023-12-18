#include "nary_trees.h"

/**
 * nary_tree_delete - deallocates an entire N-ary tree
 * @tree: pointer to root node of nary tree
 *
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *node_pointer;

	if (tree == NULL)
		return;

	while (tree)
	{
		node_pointer = tree;

		tree = tree->next;

		nary_tree_delete(
			node_pointer->children
		);
		free(node_pointer->content);
		free(node_pointer);
	}
}
