#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathfinding.h"

static int backtrack(char **, int, int, point_t *, int, int, queue_t *);

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
 * @m: pointer to a read-only two-dimensional array
 * @rs: rows of map
 * @cs: columns of map
 * @st: stores the coordinates of the starting point
 * @tg: stores the coordinates of the target point
 *
 * Return: queue in which each node is a point in the path from start to target
*/
queue_t *backtracking_array(char **m, int rs, int cs, point_t *st, point_t *tg)
{
	queue_t *path = queue_create(), *reverse_path = queue_create();
	char **copy;
	point_t *point;

	if (!path || !reverse_path)
		return (NULL);

	copy = make_copy(m, rs, cs);

	if (backtrack(copy, rs, cs, tg, st->x, st->y, path))
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
	free_copy(copy, rs);

	return (reverse_path);
}

/**
 * backtrack - uses dfs backtracking to find path
 * @m: map character grid
 * @rs: number of rows in map
 * @cs: number of columns in map
 * @tg: target point
 * @x: current x coordinate
 * @y: current y coordinate
 * @p: current path queue
 *
 * Return: 1 if target reached else 0
 */
static int backtrack(
	char **m, int rs, int cs, point_t *tg, int x, int y, queue_t *p
)
{
	point_t *point;

	if (CANT_BACKTRACK(x, y, cs, rs, m))
		return (0);

	m[y][x] = '1';

	point = create_point(x, y);
	if (point == NULL)
		return (-1);

	queue_push_front(p, point);

	printf("Checking coordinates [%d, %d]\n", x, y);

	if (REACHED_TARGET(tg, x, y))
		return (1);

	if (backtrack(m, rs, cs, tg, x + 1, y, p) ||
		backtrack(m, rs, cs, tg, x, y + 1, p) ||
		backtrack(m, rs, cs, tg, x - 1, y, p) ||
		backtrack(m, rs, cs, tg, x, y - 1, p))
		return (1);
	free(dequeue(p));

	return (0);
}
