#ifndef _RB_TREES_
#define _RB_TREES_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define IS_LEFT_CHILD(n) (\
	(n->parent != NULL) && \
	(n->parent->left != NULL) && \
	(n->parent->left == n) \
)
#define IN_ATTENDANCE(p, g) (p != NULL && g != NULL)
#define BIT_SET(n, k) (((n >> (k - 1)) & 1) == 1)

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *left_rotate(rb_tree_t *tree);
rb_tree_t *right_rotate(rb_tree_t *tree);
#endif
