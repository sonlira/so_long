/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 21:52:39 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/09 18:02:05 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_moves(t_point moves[4])
{
	moves[0].row = -1;
	moves[0].col = 0;
	moves[1].row = 1;
	moves[1].col = 0;
	moves[2].row = 0;
	moves[2].col = -1;
	moves[3].row = 0;
	moves[3].col = 1;
}

static int	is_valid_pos(t_map *map, int **visited, int row, int col)
{
	if ((row < 0 && row >= map->rows) || (col < 0 && col >= map->cols))
		return (0);
	if (visited[row][col] == 1)
		return (0);
	if (map->map[row][col] == WALL)
		return (0);
	return (1);
}

static void	apply_moves(t_map *map, int **visited, t_queue *q, t_point point)
{
	int	i;
	int	new_row;
	int	new_col;

	i = 0;
	while (i < MOVES)
	{
		new_row = point.row + map->moves[i].row;
		new_col = point.col + map->moves[i].col;
		if (is_valid_pos(map, visited, new_row, new_col))
		{
			if (map->map[new_row][new_col] == COIN)
				q->c_coins++;
			if (map->map[new_row][new_col] == EXIT)
				q->with_exit = 1;
			visited[new_row][new_col] = 1;
			enqueue(q, new_row, new_col);
		}
		i++;
	}
}

static int	find_coins_bfs(t_game *game, int **visited, t_queue *queue)
{
	t_point	point;

	get_moves(game->map->moves);
	enqueue(queue, game->player->row, game->player->col);
	while (queue->front != queue->final)
	{
		point = dequeue(queue);
		apply_moves(game->map, visited, queue, point);
	}
	if (queue->c_coins != game->t_coins || queue->with_exit != 1)
		return (0);
	return (1);
}

void	check_accessibility(t_game *game)
{
	int		**visited;
	t_queue	*q;

	if (!game)
		return ;
	visited = start_matriz_int(game->map, 0);
	if (!visited)
		error_exit("An error occurred while checking the map access");
	visited[game->player->row][game->player->col] = 1;
	q = create_queue(game->map->rows * game->map->cols);
	if (!q)
		error_exit("An error occurred while checking the map access");
	if (find_coins_bfs(game, visited, q) == 0)
	{
		free_queue(q);
		free_matriz_int(&visited, game->map->rows);
		error_exit("Unaccessible exit or collectibles");
	}
	free_queue(q);
	free_matriz_int(&visited, game->map->rows);
}
