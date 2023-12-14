#include "pathfinding.h"

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
	(void)map;
	(void)rows;
	(void)cols;
	(void)start;
	(void)target;

	return (NULL);
}
