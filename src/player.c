/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/25 23:41:28 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	measure_away(t_map *map, int **away, t_queue *queue, t_point point)
{
	int	i;
	int	new_row;
	int	new_col;

	i = 0;
	while (i < 4)
	{
		new_row = point.row + map->moves[i].row;
		new_col = point.col + map->moves[i].col;
		if (is_valid_pos(map, away, new_row, new_col))
		{
			away[new_row][new_col] = away[point.row][point.col] + 1;
			enqueue(queue, new_row, new_col);
		}
		i++;
	}
}

void	check_distance(t_game *game, int **away, t_queue *queue)
{
	t_point	point;

	enqueue(queue, game->player->pos_x, game->player->pos_y);

	while (queue->front != queue->final)
	{
		point = dequeue(queue);
		measure_away(game->map, away, queue, point);
	}
}
/*============PRIOR==============================================*/

t_point	**start_matriz_point(t_map *map)
{
	t_point	**matriz;
	int		row;
	int		col;

	if (!map)
		return (NULL);
	matriz = ft_calloc(map->rows + 1, sizeof(t_point *));
	if (!matriz)
		return (NULL);
	row = 0;
	while (row < map->rows)
	{
		matriz[row] = ft_calloc(map->cols + 1, sizeof(t_point));
		if (!matriz[row])
			return (free_matriz_point(&matriz, map->rows), NULL);
		col = 0;
		while (col < map->cols)
		{
			matriz[row][col].row = -1;
			matriz[row][col].col = -1;
			col++;
		}
		row++;
	}
	return (matriz);
}

// void	get_prior(t_map *map, int **prior, t_queue *queue, t_point point)
// {
// 	int	i;
// 	int	moves[4][2];
// 	int	new_row;
// 	int	new_col;

// 	get_moves(moves);
// 	i = 0;
// 	while (i < 4)
// 	{
// 		new_row = point.row + moves[i][0];
// 		new_col = point.col + moves[i][1];
// 		if (is_valid_pos(map, prior, new_row, new_col))
// 		{
// 			prior[new_row] = point.row;
// 			prior[new_col] = point.col;
// 			enqueue(queue, new_row, new_col);
// 		}
// 		i++;
// 	}
// }

// void 	check_prior(t_game *game, int **prior, t_queue *q)
// {
// 	t_point current;

// 	enqueue(q, game->player->pos_x, game->player->pos_y);

// 	while (q->front != q->final)
// 	{
// 		current = dequeue(q);
// 		get_prior(game->map, prior, q, current);
// 	}
// }
void	find_the_shortest_way(t_game *game)
{
	int			**distance;
	t_point		**prior;
	t_queue		*q;
	// t_queue		*q2;

	distance = start_matriz_int(game->map, -1);
	prior = start_matriz_point(game->map);
	if (!distance)
		error_exit("An error occurred when checking the shortest route");
	distance[game->player->pos_x][game->player->pos_y] = 0;
	q = create_queue(game->map->rows * game->map->cols);
	// q2 = create_queue(game->map->rows * game->map->cols);
	if (!q)
		error_exit("An error occurred when checking the shortest route");
	check_distance(game, distance, q);
	// check_prior(game, prior, q2);
	int i = 0;
	while (i < game->map->rows)
	{
		int j = 0;
		while (j < game->map->cols)
		{
			printf("(%d, %d) ", prior[i][j].row, prior[i][j].col);
			j++;
		}
		printf("\n");
		i++;
	}
	free_queue(q);
	// free_queue(q2);
	free_matriz_point(&prior, game->map->rows);
	free_matriz_int(&distance, game->map->rows);
}
