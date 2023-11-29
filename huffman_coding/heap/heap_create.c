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
	(void)data_cmp;

	return (NULL);
}
