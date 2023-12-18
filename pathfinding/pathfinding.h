#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include "graphs.h"
#include "queues.h"

#define REACHED_TARGET(t, x, y) (x == t->x && y == t->y)
#define CHECK_SIDE(axis, value) ((axis < 0) || (x >= value))
#define CANT_BACKTRACK(x, y, c, r, m) ( \
	(CHECK_SIDE(x, c)) || \
	(CHECK_SIDE(y, r)) || \
	(m[y][x] != '0'))

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct map_s - Structure storing coordinates
 * @map: pointer to a read-only two-dimensional array
 * @rows: X coordinate
 * @cols: Y coordinate
 */
typedef struct map_s
{
	char **map;
	int rows;
	int cols;
} map_t;

queue_t *backtracking_array(char **, int, int, point_t *, point_t *);
queue_t *backtracking_graph(graph_t *graph, vertex_t *start, vertex_t *target);
queue_t *dijkstra_graph(
	graph_t *graph,
	vertex_t const *start,
	vertex_t const *target
);

#endif /* _PATHFINDING_H */
