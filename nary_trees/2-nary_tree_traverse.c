#include "nary_trees.h"

#define CHILD 0
#define MAX 1

/**
 * _nary_tree_traverse - Where the real magic happens
 * @node: Current node to start traversing from
 * @dpt: Current depth of node
 * @func: A function pointer to be performed on each node
 *
 * Return: The maximum depth encountered during traversal
 */
static size_t _nary_tree_traverse(nary_tree_t *node, size_t dpt, action_t func)
{
	size_t depth[2];

	nary_tree_t *child;

	if (!node)
		return (dpt);

	func(node, dpt);

	depth[MAX] = dpt;

	for (child = node->children; child; child = child->next)
	{
		depth[CHILD] = _nary_tree_traverse(
			child, dpt + 1, func
		);
		if (depth[CHILD] > depth[MAX])
			depth[MAX] = depth[CHILD];
	}
	return (depth[MAX]);
}

/**
 * nary_tree_traverse - goes through an N-ary tree, node by node
 * @root: pointer to the root node of the tree to traverse
 * @function: pointer to a function to execute for each node being traversed.
 *
 * Return: the biggest depth of the tree pointed to by root
*/
size_t nary_tree_traverse(nary_tree_t *root, action_t function)
{
	if (root == NULL)
		return (0);

	return (
		_nary_tree_traverse(root, 0, function)
	);
}
