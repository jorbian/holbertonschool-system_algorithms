#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);
void _rb_tree_delete(rb_tree_t *tree);

/**
 * main - Entry point
 *
 * Return: Always EXIT_SUCCESS
 */
int main(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 98, BLACK);
	if (root == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}

	root->left = rb_tree_node(root, 12, RED);
	if (root->left == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}
	root->left->left = rb_tree_node(root->left, 6, BLACK);
	if (root->left->left == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}
	root->left->right = rb_tree_node(root->left, 16, BLACK);
	if (root->left->right == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}

	root->right = rb_tree_node(root, 402, RED);
	if (root->right == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}
	root->right->left = rb_tree_node(root->right, 256, BLACK);
	if (root->right->left == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}
	root->right->right = rb_tree_node(root->right, 512, BLACK);
	if (root->right->right == NULL)
	{
		printf("Failed to create RB tree node\n");
		return (EXIT_FAILURE);
	}

	rb_tree_print(root);
	_rb_tree_delete(root);
	return (EXIT_SUCCESS);
}
