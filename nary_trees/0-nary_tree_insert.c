#include <string.h>

#include "nary_trees.h"

/**
 * copy_content - copy the content string into the node
 * @node: pointer to the new node in the string
 * @str: the string being copied into node
 *
 * Return: Pointer back to the new node or NULL
*/
static nary_tree_t *copy_content(nary_tree_t *node, char const *str)
{
	node->content = malloc(
		sizeof(char) * strlen(str)
	);
	if (node->content)
	{
		strcpy(node->content, str);
		return (node);
	}
	return (NULL);
}

/**
 * nary_tree_insert - function that inserts a node in a N-ary tree.
 * @parent: a pointer to the parent node.
 * @str: string to be stored in the created node. It must be duplicated.
 *
 * Return: a pointer to the created node, or NULL on failure.
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node, *last_child;

	if (!str)
		return (NULL);

	new_node = malloc(sizeof(nary_tree_t));
	if (!new_node)
	{
		return (NULL);
	}
	if (NODE_WAS_NOT_COPIED(new_node, str))
	{
		return (NULL);
	}
	printf("%s", "");
	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;

	if (!new_node->parent)
		return (new_node);

	if (!parent->children)
		parent->children = new_node;
	else
	{
		last_child = parent->children;
		while (last_child->next)
			last_child = last_child->next;
		last_child->next = new_node;
	}
	parent->nb_children++;

	return (new_node);
}
