#include "pathfinding.h"

static map_t *copy_map_data(map_t *new_map, char **map_data);
static map_t *init_map_struct(char **map, int rows, int cols);

/**
 * solve_maze - solves a maze using backtracking
 * @map: the map to navigate
 * @rows: number of rows
 * @cols: number of cols
 * @current: coordinates of the current position
 * @target: coordinates of the target position
 * @queue: the queue that holds the final path
 * @visited: array to keep track of visited cells
 * Return: 1 if found path, else 0
*/
static int solve_maze(char **map, int rows, int cols, point_t *current,
							 point_t *target, queue_t *queue, int *visited)
{
	point_t next_move, *next_move_dup;

	int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, x, y;
	int on_target_path = 0, i;

	printf("Checking coordinates [%d, %d]\n", current->x, current->y);
	visited[(current->y * cols) + current->x] = 1;
	if (current->x == target->x && current->y == target->y)
	{
		next_move_dup = point_dup(current);
		queue_push_front(queue, (void *)next_move_dup);
		return (1);
	}
	for (i = 0; i < 4; ++i)
	{
		next_move.x = current->x + directions[i][0];
		x = next_move.x;
		next_move.y = current->y + directions[i][1];
		y = next_move.y;

		if (
			(is_valid_move(map, rows, cols, &next_move)) &&
			(!WAS_VISITED(visited, cols, x, y))
		)
			on_target_path += (
				solve_maze(map, rows, cols, &next_move, target, queue, visited)
			);
		if (on_target_path)
			break;
	}
	if (on_target_path)
		return (
			(queue_push_front(queue, (void *)point_dup(current)) != NULL)
		);

	return (0);
}

static map_t *copy_map_data(map_t *new_map, char **map_data)
{
	int i;

	new_map->map = malloc(sizeof(char *) * new_map->rows);
	if (new_map == NULL)
		return (NULL);

	for (i = 0; i < new_map->rows; i++)
		new_map->map[i] = malloc(sizeof(char) * new_map->cols);
	
	return (new_map);
}

static map_t *init_map_struct(char **map, int rows, int cols)
{
	map_t *new_map;

	new_map = malloc(sizeof(map_t));
	if (new_map == NULL)
		return (NULL);

	new_map->rows = rows;
	new_map->cols = cols;

	return (
		copy_map_data(new_map, map)
	);
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
	map_t *my_map;
	queue_t *queue;

	int *visited = calloc(sizeof(int), (rows * cols));

	my_map = init_map_struct(map, rows, cols);
	queue = queue_create();

	solve_maze(map, rows, cols, start, target, queue, visited);

	if (!queue->front)
	{
		free(queue);
		queue = NULL;
	}
	free(visited);
	return (queue);
}
