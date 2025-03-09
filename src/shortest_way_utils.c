/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortest_way_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:33:59 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/09 18:02:08 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_pocision_of_e(t_game *game)
{
	t_point	rc;

	rc.row = 0;
	while (rc.row < game->map->rows)
	{
		rc.col = 0;
		while (rc.col < game->map->cols)
		{
			if (game->map->map[rc.row][rc.col] == EXIT)
			{
				game->p_exit = rc;
				rc.row = game->map->rows;
				break ;
			}
			rc.col++;
		}
		rc.row++;
	}
}

static t_point	*get_pocisions_of_coins(t_game *game)
{
	t_point	*coins;
	t_point	rc;
	int		i;

	coins = ft_calloc(game->t_coins, sizeof(t_point));
	if (!coins)
		return (NULL);
	rc.row = 0;
	i = 0;
	while (rc.row < game->map->rows && i < game->t_coins)
	{
		rc.col = 0;
		while (rc.col < game->map->cols)
		{
			if (game->map->map[rc.row][rc.col] == COIN)
			{
				coins[i] = rc;
				i++;
			}
			rc.col++;
		}
		rc.row++;
	}
	return (coins);
}

int	get_pocisions_of_items(t_game *game)
{
	t_point	player;
	t_point	*coins;
	t_point	rc;

	if (!game)
		return (0);
	player.row = game->player->row;
	player.col = game->player->col;
	coins = get_pocisions_of_coins(game);
	if (!coins)
		return (0);
	game->locations = ft_calloc(game->t_coins + 2, sizeof(t_point));
	if (!game->locations)
		return (free(coins), 0);
	get_pocision_of_e(game);
	rc.col = 0;
	game->locations[rc.col++] = player;
	rc.row = 0;
	while (rc.row < game->t_coins)
		game->locations[rc.col++] = coins[rc.row++];
	game->locations[rc.col] = game->p_exit;
	return (free(coins), 1);
}

int	**init_costs(t_game *game)
{
	int	**matriz;
	int	row;

	if (!game)
		return (NULL);
	if (game->t_coins < 1)
		return (NULL);
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
