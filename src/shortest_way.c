/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/27 00:11:53 by abaldelo         ###   ########.fr       */
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

int	low_cost(t_game *game)
{
	int		**costs;
	int		low_cost;
	int		sum_cost;
	t_point	rc;

	costs = calculate_costs(game);
	if (!costs)
		return (-1);
	low_cost = INT_MAX;
	rc.row = -1;
	while (++rc.row < game->t_coins + 2)
	{
		rc.col = -1;
		sum_cost = 0;
		while (++rc.col < game->t_coins + 2)
			sum_cost += costs[rc.row][rc.col];
		if (sum_cost < low_cost)
			low_cost = sum_cost;
		printf("fila[ %d ] cost =( %d )\n", rc.row, low_cost);
	}
	return (free_matriz_int(&costs, game->t_coins + 2), low_cost);
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