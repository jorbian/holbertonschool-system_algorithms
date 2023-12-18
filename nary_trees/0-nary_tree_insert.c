#include <string.h>

#include "nary_trees.h"


/**
 * free_node - checks if node had content buffer and then frees it and buffer
 * @node: the node being freed
 *
 * Return: ALWAYS NULL
*/
static nary_tree_t *free_node(nary_tree_t *node)
{
	if (node->content)
		free(node->content);

	free(node);

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
	nary_tree_t *new_node;

	char *node_content;

	new_node = malloc(sizeof(nary_tree_t));
	if (new_node == NULL)
		return (NULL);

	node_content = strdup(str);
	if (node_content == NULL)
		return (free_node(new_node));

	new_node->children = NULL;
	new_node->content = node_content;
	new_node->nb_children = 0;
	new_node->next = NULL;
	new_node->parent = parent;

	if (parent)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children++;
	}
	return (new_node);
}
