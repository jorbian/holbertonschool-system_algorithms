#include "rb_trees.h"

#define FLIP_COLORS(n1, n2) (n1->color = BLACK, n2->color = RED)


static void perform_rotations(
	rb_tree_t **pos,
	rb_tree_t **parent,
	rb_tree_t **gp
)
{
	if IS_LEFT_CHILD((*parent))
		right_rotate(*gp);
	else
		left_rotate(*gp);

	if (IS_LEFT_CHILD((*parent)) == IS_LEFT_CHILD((*pos)))
		FLIP_COLORS((*parent), (*gp));
	else
	{
		FLIP_COLORS((*pos), (*gp));
		if (IS_LEFT_CHILD((*pos)))
			right_rotate(*parent);
		else
			left_rotate(*parent);
	}
}

/**
 * gather_family - updates all our "related" pointers
 * @tree_pos: current node we're looking at.
 * @parent: it's parent node
 * @uncle: parent's sibling node
 * @gp: the grandparent node
 *
*/
static void gather_family(
	rb_tree_t *tree_pos,
	rb_tree_t **parent,
	rb_tree_t **uncle,
	rb_tree_t **gp
)
{
	if (tree_pos->parent)
		* parent = tree_pos->parent;
	else
	{
		*parent = NULL;
	}
	if (tree_pos->parent && tree_pos->parent->parent)
	{
		if (tree_pos->parent->parent->left == tree_pos->parent)
			* uncle = (tree_pos->parent->parent->right);
		else
			*uncle = (tree_pos->parent->parent->left);
	}
	if (!*uncle)
		* uncle = NULL;

	if (*parent)
	{
		*gp = (*parent)->parent;
	}
	else
	{
		*gp = NULL;
	}
	if (!*gp)
		* gp = NULL;
}

/**
 * bst_insert - inserts a node in order on a given tree
 * @root: pointer to the root node of a tree
 * @new: double pointer to the newly created node
 * Return: pointer to the newly created node
*/
static rb_tree_t *bst_insert(rb_tree_t *root, rb_tree_t **new)
{
	if (!new)
		return (NULL);
	if (!root)
	{
		root = *new;
		return (*new);
	}
	if ((*new)->n == root->n)
	{
		free(*new);
		*new = NULL;
		return (root);
	}
	(*new)->parent = root;
	if ((*new)->n > root->n)
		root->right = bst_insert(root->right, new);
	else
		root->left = bst_insert(root->left, new);

	if (root->right)
		root->right->parent = root;
	if (root->left)
		root->left->parent = root;

	return (root);

}

/**
 * family_counseling - fixes a red-black tree after new node is added
 * @root: pointer to the root of a tree
 * @new: the newly created node that was inserted
 * Return: pointer to the root of the tree
*/
static rb_tree_t *family_counseling(rb_tree_t *root, rb_tree_t *new)
{
	rb_tree_t *parent = NULL, *uncle = NULL, *gp = NULL, *pos = NULL;

	if (!new)
		return (root);
	pos = new;
	gather_family(pos, &parent, &uncle, &gp);
	if (!parent)
	{
		pos->color = BLACK;
		return (root = pos);
	}

	while (IN_ATTENDANCE(parent, gp))
	{
		if (parent->color == RED && (uncle && uncle->color == RED))
		{
			parent->color = BLACK;
			uncle->color = BLACK;
			gp->color = RED;
			pos = gp;
			gather_family(pos, &parent, &uncle, &gp);
			continue;
		}
		if (parent->color == RED && (!uncle || uncle->color == BLACK))
			perform_rotations(&pos, &parent, &gp);
		pos = gp;
		gather_family(pos, &parent, &uncle, &gp);
	}

	if (parent)
	{
		if (parent->color == RED)
			pos->color = BLACK;
		root = parent;
	}
	else
		root = pos;
	root->color = BLACK;
	return (root);

}

/**
 * rb_tree_insert - inserts a node following Red Black tree requirments
 * @tree: double pointer to the root of a given tree
 * @value: value to be stored in the newly created node
 * Return: pointer to the newly created node
*/
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node, *new;

	node = *tree;
	new = rb_tree_node(NULL, value, RED);
	node = bst_insert(node, &new);
	node = family_counseling(node, new);
	*tree = node;
	return (new);
}
