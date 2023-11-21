#include "graphs.h"

/**
 * graph_add_edge - adds an edge between two vertices to an existing graph
 * @graph: pointer to the graph to add the edge to
 * @src: string identifying the vertex to make the connection from
 * @dest: string identifying the vertex to connect to
 * @type: the type of edge
 *
 * Return: 1 on success, or 0 on failure
*/
int graph_add_edge(
	graph_t *graph,
	const char *src,
	const char *dest,
	edge_type_t type
)
{
	(void)graph;
	(void)src;
	(void)dest;
	(void)type;

	return (0);
}
