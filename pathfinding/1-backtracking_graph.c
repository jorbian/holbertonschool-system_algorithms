#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathfinding.h"

static char *g_visited;
static queue_t *g_path;
static vertex_t const *g_target;
static graph_t *g_graph;

/**
 * depth_first_search - uses depth-first search to find path
 * @vertex: current vertex to traverse
 *
 * Return: '1' if destination was found else '0'
 */
int depth_first_search(vertex_t *vertex)
{
	char *city;
	edge_t *edge;

	if (g_visited[vertex->index])
		return (0);

	printf("Checking %s\n", vertex->content);
	g_visited[vertex->index] = 1;

	city = strdup(vertex->content);
	if (!city)
		return (-1);

	queue_push_front(g_path, city);
	if (vertex == g_target)
		return (1);

	for (edge = vertex->edges; edge; edge = edge->next)
		if (depth_first_search(edge->dest))
			return (1);
	free(dequeue(g_path));
	return (0);
}

/**
 * backtracking_graph - search for first path to a target in graph.
 * @graph: pointer to the graph to go through
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: queue in which each node is string corresponding to vertex
*/
queue_t *backtracking_graph(graph_t *graph, vertex_t *start, vertex_t *target)
{
	char *city;
	queue_t *reverse_path = NULL;

	if (!graph || !start || !target)
		return (NULL);

	setbuf(stdout, NULL);
	g_visited = calloc(graph->nb_vertices, sizeof(*g_visited));
	g_path = queue_create();
	if (!g_visited || !g_path)
		return (NULL);
	g_target = target;
	g_graph = graph;
	if (depth_first_search(start))
	{
		reverse_path = queue_create();
		if (!reverse_path)
			return (NULL);

		while ((city = dequeue(g_path)))
		{
			if (!queue_push_front(reverse_path, city))
				return (NULL);
		}
	}
	queue_delete(g_path);
	free(g_visited);
	return (reverse_path);
}
