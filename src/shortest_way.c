/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/27 23:59:08 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static t_point	**start_matriz_point(t_map *map)
// {
// 	t_point	**matriz;
// 	int		row;
// 	int		col;

// 	matriz = ft_calloc(map->rows, sizeof(t_point *));
// 	if (!matriz)
// 		return (NULL);
// 	row = 0;
// 	while (row < map->rows)
// 	{
// 		matriz[row] = ft_calloc(map->cols, sizeof(t_point));
// 		if (!matriz[row])
// 			return (free_matriz_point(&matriz, map->rows), NULL);
// 		col = 0;
// 		while (col < map->cols)
// 		{
// 			matriz[row][col].row = -1;
// 			matriz[row][col].col = -1;
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (matriz);
// }
/*================distancebfs======================*/
static int	is_valid_pos(t_map *map, int **visited, int nr, int nc)
{
	if ((nr < 0 && nr >= map->rows) || (nc < 0 && nc >= map->cols))
		return (0);
	if (visited[nr][nc] != -1)
		return (0);
	if (map->map[nr][nc] == WALL)
		return (0);
	return (1);
}

static void	apply_moves(t_map *map, int **away, t_queue *q, t_point point)
{
	int		i;
	t_point	new;

	i = 0;
	while (i < MOVES)
	{
		new.row = point.row + map->moves[i].row;
		new.col = point.col + map->moves[i].col;
		if (is_valid_pos(map, away, new.row, new.col))
		{
			away[new.row][new.col] = away[point.row][point.col] + 1;
			enqueue(q, new.row, new.col);
		}
		i++;
	}
}

static int	distance_bfs(t_game *game, t_point start, t_point end)
{
	t_queue	*queue;
	t_point	point;
	int		**away;
	int		distance;

	away = start_matriz_int(game->map, -1);
	if (!away)
		return (-1);
	queue = create_queue(game->map->rows * game->map->cols);
	if (!queue)
		return (free_matriz_int(&away, game->map->rows), -1);
	away[start.row][start.col] = 0;
	enqueue(queue, start.row, start.col);
	while (queue->front != queue->final)
	{
		point = dequeue(queue);
		if (point.row == end.row && point.col == end.col)
			break ;
		apply_moves(game->map, away, queue, point);
	}
	distance = away[end.row][end.col];
	free_matriz_int(&away, game->map->rows);
	free_queue(queue);
	return (distance);
}
/*================distancebfs======================*/

/*===================================================*/

/*===================================*/

static int	**init_costs(t_game *game)
{
	int	**matriz;
	int	row;

	matriz = ft_calloc(game->t_coins + 2, sizeof(int *));
	if (!matriz)
		return (NULL);
	row = 0;
	while (row < game->t_coins + 2)
	{
		matriz[row] = ft_calloc(game->t_coins + 2, sizeof(int));
		if (!matriz[row])
			return (free_matriz_int(&matriz, game->t_coins + 2), NULL);
		row++;
	}
	return (matriz);
}

int	**calculate_costs(t_game *g)
{
	int		**costs;
	t_point	*se;
	t_point	rc;

	costs = init_costs(g);
	if (!costs)
		return (NULL);
	se = g->locations;
	rc.row = -1;
	while (++rc.row < g->t_coins + 2)
	{
		rc.col = -1;
		while (++rc.col < g->t_coins + 2)
		{
			if (rc.row != rc.col)
				costs[rc.row][rc.col] = distance_bfs(g, se[rc.row], se[rc.col]);
			else
				costs[rc.row][rc.col] = 0;
			printf("[ %d ]", costs[rc.row][rc.col]);
		}
		printf("\n");
	}
	return (costs);
}

void	item_visited(int **costs, int col, int size)
{
	int	row;

	row = -1;
	while (++row < size)
		costs[row][col] = -1; 
}

int	is_time_to_e(int **costs, int row, int size)
{
	int col;
	int	count_v;

	col = -1;
	count_v = 0;
	while (++col < size)
	{
		if (costs[row][col] == -1)
			count_v++;
	}
	return (count_v == size -1);
}

int	low_cost(t_game *game)
{
	int		**costs;
	t_rute	ic;
	int		size;
	t_point	rc;
	int		visit;
	t_rute	rute[1024];

	costs = calculate_costs(game);
	if (!costs)
		return (free(game->locations),-1);
	rute[0].rc = game->locations[0];
	item_visited(costs, 0, game->t_coins + 2);
	ic.rc.col = 1;
	size = game->t_coins + 1;
	rc.row = 0;
	while (size != game->t_coins + 2)
	{
		ic.cost = INT_MAX;
		visit = 0;
		if (is_time_to_e(costs, rc.row, size))
			size++;
		rc.col = -1;
		while (++rc.col < size)
		{
			if (costs[rc.row][rc.col] != 0 && costs[rc.row][rc.col] != -1)
			{
				if (costs[rc.row][rc.col] < ic.cost)
				{
					ic.cost = costs[rc.row][rc.col];
					rute[ic.rc.col].rc = game->locations[rc.col];
					rute[ic.rc.col].cost = ic.cost;
					visit = rc.col;
				}
			}
		}
		item_visited(costs, visit, game->t_coins + 2);
		ic.rc.col++;
		rc.row = visit;
	}
	rc.col = -1;
	while(++rc.col < size)
	{
		if(costs[visit][rc.col] != -1)
		{
			rute[ic.rc.col].rc = game->locations[rc.col];
			rute[ic.rc.col].cost = costs[visit][rc.col];
			visit = rc.col;
		}
	}
	return (free(game->locations),free_matriz_int(&costs, game->t_coins + 2), 0);
}

/*====================================*/
void	find_the_shortest_way(t_game *game)
{
	// t_point		**prior;
	// prior = start_matriz_point(game->map);
	// if (!distance || !prior)
	// 	error_exit("An error occurred when checking the shortest route");
	// distance[game->player->row][game->player->col] = 0;
	if (get_pocisions_of_items(game) == 0)
		error_exit("An error occurred when checking the shortest route");
	// if (!queue->locations)
	// 	error_exit("An error occurred when checking the shortest route");
	// get_pocision_of_e(game, queue);
	// printf("hola");
	printf("cost %d", low_cost(game));
	// for(int i = 0; i < game->map->rows; i++)
	// {
	// 	printf("%s\n", game->map->map[i]);
	// }
	// for(int i = 0; i < game->map->rows; i++)
	// {
	// 	for(int j = 0; j < game->map->cols; j++)
	// 	{
	// 		printf("%d", distance[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// for(int i = 0; i < game->t_coins; i++)
	// {
	// 	printf("(%d, %d)", queue->locations[i].row, queue->locations[i].col);
	// }
	// printf("\n");
	// printf("(%d, %d)\n", queue->exit.row, queue->exit.col);
	// free_matriz_point(&prior, game->map->rows);
	// free_matriz_int(&distance, game->map->rows);
}
	// // while (exit.row != -1 && exit.col != -1)
	// // {
	// // 	printf("(%d, %d) <- ", exit.row, exit.col);
	// // 	exit = prior[exit.row][exit.col];
	// // }
	// printf("\n");