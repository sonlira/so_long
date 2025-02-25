/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/26 00:15:30 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	**start_matriz_point(t_map *map)
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

static void	dis_and_pri_bfs(t_game *game, int **away, t_point **pri, t_queue *q)
{
	t_point	point;
	int		i;
	int		new_row;
	int		new_col;

	enqueue(q, game->player->pos_x, game->player->pos_y);
	while (q->front != q->final)
	{
		point = dequeue(q);
		i = 0;
		while (i < MOVES)
		{
			new_row = point.row + game->map->moves[i].row;
			new_col = point.col + game->map->moves[i].col;
			if (is_valid_pos(game->map, away, new_row, new_col))
			{
				away[new_row][new_col] = away[point.row][point.col] + 1;
				pri[new_row][new_col].row = point.row;
				pri[new_row][new_col].col = point.col;
				enqueue(q, new_row, new_col);
			}
			i++;
		}
	}
}
/*============PRIOR==============================================*/


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
	t_queue		*queue;

	distance = start_matriz_int(game->map, -1);
	prior = start_matriz_point(game->map);
	if (!distance || !prior)
		error_exit("An error occurred when checking the shortest route");
	distance[game->player->pos_x][game->player->pos_y] = 0;
	queue = create_queue(game->map->rows * game->map->cols);
	if (!queue)
		error_exit("An error occurred when checking the shortest route");
	dis_and_pri_bfs(game, distance, prior, queue);
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
	free_queue(queue);
	// free_queue(q2);
	free_matriz_point(&prior, game->map->rows);
	free_matriz_int(&distance, game->map->rows);
}
