/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/26 01:01:22 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_point	**start_matriz_point(t_map *map)
{
	t_point	**matriz;
	int		row;
	int		col;

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

	enqueue(q, game->player->row, game->player->col);
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

static void	get_the_char_position(t_game *game, t_point *point, char character)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map->rows)
	{
		col = 0;
		while (col < game->map->cols)
		{
			if (game->map->map[row][col] == character)
			{
				point->row = row;
				point->col = col;
				row = game->map->rows;
				break ;
			}
			col++;
		}
		row++;
	}
}

void	find_the_shortest_way(t_game *game)
{
	int			**distance;
	t_point		**prior;
	t_queue		*queue;
	t_point		actual;

	distance = start_matriz_int(game->map, -1);
	prior = start_matriz_point(game->map);
	if (!distance || !prior)
		error_exit("An error occurred when checking the shortest route");
	distance[game->player->row][game->player->col] = 0;
	queue = create_queue(game->map->rows * game->map->cols);
	if (!queue)
		error_exit("An error occurred when checking the shortest route");
	dis_and_pri_bfs(game, distance, prior, queue);
	get_the_char_position(game, &actual, EXIT);
	while (actual.row != -1 && actual.col != -1)
	{
		printf("(%d, %d) <- ", actual.row, actual.col);
		actual = prior[actual.row][actual.col];
	}
	printf("\n");

	free_queue(queue);
	free_matriz_point(&prior, game->map->rows);
	free_matriz_int(&distance, game->map->rows);
}
