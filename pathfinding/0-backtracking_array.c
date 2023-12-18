#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathfinding.h"

static int backtrack(char **map, int rows, int cols, point_t const *target,
	int x, int y, queue_t *path);

/**
 * make_copy - copy the map being backtracked over
 * @original: the original copy of the map
 * @x: rows in the map
 * @y: columns of the map
 *
 * Return: a pointer to the copy of the new map.
*/
static char **make_copy(char **original, int x, int y)
{
	int i;

	char **copy;

	copy = malloc(x * sizeof(char *));
	if (!copy)
		return (NULL);

	for (i = 0; i < x; i++)
	{
		copy[i] = malloc(y + 1);
		if (!copy[i])
			return (NULL);
		strcpy(copy[i], original[i]);
	}
	return (copy);
}

/**
 * free_copy - deallocates memory used for copy
 * @copy: the copy of the map used to backtrack over
 * @rows: number of rows it included.
 *
*/
static void free_copy(char **copy, int rows)
{
	int i;

	for (i = 0; i < rows; i++)
		free(copy[i]);
	free(copy);
}

/**
 * create_point - initalizes the point_t struct
 * @x: the x value to store in point
 * @y: the y value to store in point
 *
 * Return: Pointer to pointlessly eheap allocated struct
*/
static point_t *create_point(int x, int y)
{
	point_t *new_point;

	new_point = calloc(1, sizeof(*new_point));
	if (!new_point)
		return (NULL);

	new_point->x = x;
	new_point->y = y;

	return (new_point);
}

/**
 * backtracking_array - search for first path from a starting point to target.
 * @map: pointer to a read-only two-dimensional array
 * @rows: rows of map
 * @cols: columns of map
 * @start: stores the coordinates of the starting point
 * @target: stores the coordinates of the target point
 *
 * Return: queue in which each node is a point in the path from start to target
*/
queue_t *backtracking_array(
	char **map,
	int rows,
	int cols,
	point_t const *start,
	point_t const *target
)
{
	queue_t *path = queue_create(), *reverse_path = queue_create();
	char **copy;
	point_t *point;

	if (!path || !reverse_path)
		return (NULL);

	copy = make_copy(map, rows, cols);

	if (backtrack(copy, rows, cols, target, start->x, start->y, path))
	{
		while ((point = dequeue(path)))
			queue_push_front(reverse_path, point);
		free(path);
	}
	else
	{
		free(path);
		free(reverse_path);
		reverse_path = NULL;
	}
	free_copy(copy, rows);

	return (reverse_path);
}

/**
 * backtrack - uses dfs backtracking to find path
 * @map: map character grid
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @target: target point
 * @x: current x coordinate
 * @y: current y coordinate
 * @path: current path queue
 *
 * Return: 1 if target reached else 0
 */
static int backtrack(char **map, int rows, int cols, point_t const *target,
	int x, int y, queue_t *path)
{
	point_t *point;

	if (CANT_BACKTRACK(x, y, cols, rows, map))
		return (0);

	map[y][x] = '1';

	point = create_point(x, y);
	if (point == NULL)
		return (-1);

	queue_push_front(path, point);

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (REACHED_TARGET(target, x, y))
		return (1);

	if (backtrack(map, rows, cols, target, x + 1, y, path) ||
		backtrack(map, rows, cols, target, x, y + 1, path) ||
		backtrack(map, rows, cols, target, x - 1, y, path) ||
		backtrack(map, rows, cols, target, x, y - 1, path))
		return (1);
	free(dequeue(path));

	return (0);
}
