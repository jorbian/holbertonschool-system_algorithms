#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <stdlib.h>
#include "./heap/heap.h"

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);

#endif /* __HUFFMAN_H_ */
