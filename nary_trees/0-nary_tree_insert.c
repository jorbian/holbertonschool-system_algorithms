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
 * initalize_fields - initalize fields of node to default values
 * @node: the new node being created
 * @content: a pointer to whatever it contains
 *
*/
static void initalize_fields(nary_tree_t *node, char *content)
{
	node->children = NULL;
	node->content = content;
	node->nb_children = 0;
	node->next = NULL;
}

/**
 * adjust_parent_node - adjusts the parent to make sure information is right
 * @node: the node being created
 * @parent: pointer to the parent
 *
*/
static void adjust_parent_node(nary_tree_t *node, nary_tree_t *parent)
{
	node->parent = parent;

	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
		parent->nb_children++;
	}
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

	initalize_fields(new_node, node_content);
	adjust_parent_node(new_node, parent);

	return (new_node);
}
