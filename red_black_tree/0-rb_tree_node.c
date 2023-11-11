#include "rb_trees.h"

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