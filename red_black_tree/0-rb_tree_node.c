#include "rb_trees.h"

#define NEW 0
#define OLD 1

/**
 * rb_tree_node - allocate a red-black tree node and initalize values
 * @parent: the parent node that it's being added to
 * @value: the value that needs to be placed in the node
 * @color: the color the new node is supposed to have
 *
 * Return: a pointer to the newly allocated node
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;

	new = malloc(sizeof(rb_tree_t));
	if (new == NULL)
		return (NULL);

	new->n = value;
	new->color = color;
	new->parent = parent;

	new->left = NULL;
	new->right = NULL;

	return (new);
}

/**
 * left_rotate - Rotates a binary search tree clockwise
 * @tree: The binary search tree to rotate
 *
 * Return: The newly rotated binary search tree
*/
rb_tree_t *left_rotate(rb_tree_t *tree)
{
	rb_tree_t *roots[2] = {NULL, NULL};
	rb_tree_t *old_left;

	if (!tree || !tree->right)
		return (tree);

	roots[OLD] = tree;
	roots[NEW] = tree->right;
	if (tree->right->left)
	{
		old_left = tree->right->left;
		old_left->parent = roots[OLD];
		roots[OLD]->right = old_left;
	}
	else
		roots[OLD]->right = NULL;
	if (roots[OLD]->parent)
	{
		if (roots[OLD] == roots[OLD]->parent->left)
			roots[OLD]->parent->left = roots[NEW];
		else
			roots[OLD]->parent->right = roots[NEW];
	}
	roots[NEW]->parent = roots[OLD]->parent;
	roots[OLD]->parent = roots[NEW];
	roots[NEW]->left = roots[OLD];

	return (roots[NEW]);
}

/**
 * right_rotate - Rotates a binary search tree clockwise
 * @tree: The binary search tree to rotate
 *
 * Return: The newly rotated binary search tree
*/
rb_tree_t *right_rotate(rb_tree_t *tree)
{
	rb_tree_t *roots[2] = {NULL, NULL};
	rb_tree_t *old_right;

	if (!tree || !tree->left)
		return (tree);

	roots[OLD] = tree;
	roots[NEW] = tree->left;

	if (tree->left->right)
	{
		old_right = tree->left->right;
		old_right->parent = roots[OLD];
		roots[OLD]->left = old_right;
	}
	else
		roots[OLD]->left = NULL;

	if (roots[OLD]->parent)
	{
		if (roots[OLD] == roots[OLD]->parent->left)
			roots[OLD]->parent->left = roots[NEW];
		else
			roots[OLD]->parent->right = roots[NEW];
	}
	roots[NEW]->parent = tree->parent;
	roots[NEW]->right = roots[OLD];
	roots[OLD]->parent = roots[NEW];

	return (roots[NEW]);
}
