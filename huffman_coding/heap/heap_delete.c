#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

/**
 * heap_delete - deallocates a heap
 * @heap: pointer to the heap to delete
 * @free_data: pointer to function that will be used to free content of nodes
 *
*/
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	(void)heap;
	(void)free_data;
}
