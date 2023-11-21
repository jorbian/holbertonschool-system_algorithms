#include "graphs.h"

/**
 * depth_first_traverse - goes through graph using depth-first algorithm.
 * @graph: pointer to the graph to traverse.
 * @action: pointer to function to be called for each visited vertex
 *
 * Return: biggest vertex depth, or 0 on failure
*/
size_t depth_first_traverse(
	const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth)
)
{
	(void)graph;
	(void)action;

	return (0);
}
