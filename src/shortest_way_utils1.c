/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_way_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:24:50 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/28 19:50:50 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	**calculate_costs(t_game *g)
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

static void	item_visited(int **costs, int col, int size)
{
	int	row;

	row = -1;
	while (++row < size)
		costs[row][col] = -1;
}

static int	is_time_to_e(int **costs, int row, int size)
{
	int	col;

	col = -1;
	while (++col < size)
	{
		if (costs[row][col] > 0)
			return (0);
	}
	return (1);
}

static int	lower_cost(t_game *game, int **costs, t_point r, int size)
{
	t_point	next;

	next.row = 0;
	next.col = -1;
	while (++next.col < size)
	{
		if (costs[r.row][next.col] > 0)
		{
			if (costs[r.row][next.col] < game->rute[r.col].cost)
			{
				game->rute[r.col].rc = game->locations[next.col];
				game->rute[r.col].cost = costs[r.row][next.col];
				next.row = next.col;
			}
		}
	}
	return (next.row);
}

int	best_pick_up_order(t_game *game)
{
	int		**costs;
	int		size;
	t_point	r;

	if (!game)
		return (-1);
	costs = calculate_costs(game);
	if (!costs)
		return (free(game->locations), free(game->rute), -1);
	game->rute[0].rc = game->locations[0];
	game->rute[0].cost = 0;
	item_visited(costs, 0, game->t_coins + 2);
	size = game->t_coins + 1;
	r.col = 1;
	r.row = 0;
	while (size != game->t_coins + 2)
	{
		game->rute[r.col].cost = INT_MAX;
		if (is_time_to_e(costs, r.row, size))
			size++;
		r.row = lower_cost(game, costs, r, size);
		item_visited(costs, r.row, game->t_coins + 2);
		r.col++;
	}
	return (free(game->locations), free_matriz_int(&costs, size), 1);
}
