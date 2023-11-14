#include "rb_trees.h"

static size_t rb_height(const rb_tree_t *tree);

/**
 * rb_height - Measures the height of binary tree.
 * @tree: Pointer to root node to measure the height.
 *
 * Return: Tree is NULL, function returns 0, else returns the height.
 */
static size_t rb_height(const rb_tree_t *tree)
{
	size_t height_l;
	size_t height_r;

	height_l = tree->left ? 1 + rb_height(tree->left) : 0;
	height_r = tree->right ? 1 + rb_height(tree->right) : 0;

	return (
		(height_l > height_r) ? height_l : height_r
	);
}

/**
  * is_bst - recursive function to validate BST
  * @tree: node that's currently being checked
  * @min: current minimum acceptable value
  * @max: current max
  *
  * Return: Whether a branch of the tree was validated.
 */
static int is_bst(rb_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n < min || tree->n > max)
		return (0);

	return (
		(is_bst(tree->left, min, tree->n - 1)) &&
		(is_bst(tree->right, tree->n + 1, max))
	);
}

/**
 * validate_bst - checks if a binary tree is a valid Binary Search Tree
 * @tree: pointer to the root node of binary tree being examined
 *
 * Return: 1 if tree is a valid BST, and 0 otherwise
*/
static int validate_bst(rb_tree_t *tree)
{
	return (is_bst(tree, INT_MIN, INT_MAX));
}

/**
 * validate_colors - Go down each node of tree to see if it's painted right
 * @tree: The tree to check the colors of
 *
 * Return: 1/true if true, 0/false if false
*/
static int validate_colors(rb_tree_t *tree)
{
	rb_color_t color;

	if (tree == NULL)
		return (1);

	color = tree->color;

	if (!IN_RANGE(color, RED, BLACK))
		return (0);

	if (color == BLACK)
	{
		if (
			(tree->left && (tree->left)->color == RED) ||
			(tree->right && (tree->right)->color == RED)
		)
			return (0);
	}
	return (
		validate_colors(tree->left) &&
		validate_colors(tree->right)
	);
}

/**
 * count_black_nodes - Count the number of black nodes
 * @root: Root node of an RB tree
 *
 * Return: Number of black nodes in the tree
*/
static size_t count_black_nodes(rb_tree_t *root)
{
	int height;

	if (root == NULL)
		return (0);

	height = MAX(
		count_black_nodes(root->left),
		count_black_nodes(root->right)
	);
	if (root->color == BLACK)
		height++;

	return (height);
}

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to the root node of the tree to check
 *
 * Return: '1' if tree is a valid Red-Black Tree, and '0' otherwise
*/
int rb_tree_is_valid(rb_tree_t *tree)
{
	return (
		(tree != NULL) &&
		(tree->color == BLACK) &&
		(validate_colors(tree) && validate_bst(tree)) &&
		(rb_height(tree) < (2 * count_black_nodes(tree)))
	);
}
