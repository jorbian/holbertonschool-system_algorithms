#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

/**
 * heap_create - creates heap data structure
 * @data_cmp: pointer to a comparison function
 *
 * Return: pointer to new heap_t data structure, or NULL on failure
*/
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new_heap;

	new_heap = malloc(sizeof(heap_t));
	if (new_heap == NULL)
		return (NULL);

	new_heap->size = 0;
	new_heap->data_cmp = data_cmp;
	new_heap->root = NULL;

	return (new_heap);
}
