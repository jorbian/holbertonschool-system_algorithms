#include "rb_trees.h"

/**
 * rb_tree_node - creates a new node for a RB tree
 * @parent: pointer to parent node of the newly created node
 * @value: the value to be stored in the new node
 * @color: color of the newly created node
 * Return: pointer to the new node, NULL on error
*/

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new;

	new = malloc(sizeof(rb_tree_t));
	if (!new)
		return (NULL);
	if (!parent)
		parent = NULL;
	new->parent = parent;
	new->n = value;
	if (!color)
		new->color = RED;
	else
		new->color = RED;
	new->left = NULL;
	new->right = NULL;

	return (new);
}

/**
 * left_rotate - balances a tree by rotating nodes left
 * @tree: pointer to the root of a tree
 * Return: pointer to the new root
*/
rb_tree_t *left_rotate(rb_tree_t *tree)
{
	rb_tree_t *new_root, *old_root, *old_left;

	if (tree == NULL || tree->right == NULL)
		return (tree);

	old_root = tree;
	new_root = tree->right;
	if (tree->right->left)
	{
		old_left = tree->right->left;
		old_left->parent = old_root;
		old_root->right = old_left;
	}
	else
		old_root->right = NULL;
	if (old_root->parent)
	{
		if (old_root == old_root->parent->left)
			old_root->parent->left = new_root;
		else
			old_root->parent->right = new_root;
	}
	new_root->parent = old_root->parent;
	old_root->parent = new_root;
	new_root->left = old_root;

	return (new_root);
}

/**
 * right_rotate - balances a tree by rotating nodes right
 * @tree: pointer to the root of a tree
 * Return: pointer to the new root
*/
rb_tree_t *right_rotate(rb_tree_t *tree)
{
	rb_tree_t *old_root, *new_root, *old_right;

	if (tree == NULL || tree->left == NULL)
		return (tree);

	old_root = tree;
	new_root = tree->left;

	if (tree->left->right)
	{
		old_right = tree->left->right;
		old_right->parent = old_root;
		old_root->left = old_right;
	}
	else
		old_root->left = NULL;

	if (old_root->parent)
	{
		if (old_root == old_root->parent->left)
			old_root->parent->left = new_root;
		else
			old_root->parent->right = new_root;
	}
	new_root->parent = tree->parent;
	new_root->right = old_root;
	old_root->parent = new_root;

	return (new_root);
}
