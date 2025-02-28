/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_way.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:22 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/28 21:01:47 by abaldelo         ###   ########.fr       */
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

int	distance_bfs(t_game *game, t_point start, t_point end)
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

static void	total_cost_of_the_route(t_game *game)
{
	int	col;

	col = -1;
	game->max_moves = 0;
	while (++col < game->t_coins + 2)
		game->max_moves += game->rute[col].cost;
}

int	find_the_shortest_way(t_game *game)
{
	if (!game)
		return (0);
	if (get_pocisions_of_items(game) == 0)
		return (free_matriz(&game->map->map), 0);
	game->rute = ft_calloc(game->t_coins + 2, sizeof(t_rute));
	if (!game->rute)
		return (free(game->locations), free_matriz(&game->map->map), 0);
	if (best_pick_up_order(game) == -1)
		return (free(game->rute),free_matriz(&game->map->map), 0);
	total_cost_of_the_route(game);
	return (1);
}
