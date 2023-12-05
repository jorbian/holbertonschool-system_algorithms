#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

/**
 * place_higher - does exactly what it says on the tin
 * @heap: pointer to the heap
 * @current_node: pointer the current node
 *
 */
static void place_higher(heap_t *heap, node_t *current_node)
{
	node_t *parent;

	while (current_node->parent)
	{
		parent = current_node->parent;

		if (heap->data_cmp(parent->data, current_node->data) > 0)
		{
			parent->data = current_node->data;
			current_node->data = parent->data;
			current_node = parent;
		}
		else
			break;
	}
}

/**
 * heap_insert - inserts a value in a Min Binary Heap
 * @heap: pointer to the heap in which the node has to be inserted
 * @data: pointer containing data to store in new node
 *
 * Return: pointer to new node containing data, or NULL if it fails
*/
node_t *heap_insert(heap_t *heap, void *new_data)
{
	node_t *new_node;

	if (!heap || !new_data)
		return (NULL);

	new_node = binary_tree_node(heap->root, new_data);
	if (!new_node)
		return (NULL);

	if (!heap->root)
		heap->root = new_node;
	else
		place_higher(heap, new_node);

	heap->size++;

	return (new_node);
}
