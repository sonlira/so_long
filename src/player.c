/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/03 01:29:27 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_coin(t_game *game, t_point new)
{
	t_point	rc;

	rc.row = new.row / PX;
	rc.col = new.col / PX;
	if (game->map->map[rc.row][rc.col] == COIN)
	{
		ft_putendl_fd("💰 Collectible found!!! 👏", EXIT_SUCCESS);
		game->player->p_moves++;
		game->player->p_coins++;
	}
}

static void	is_exit(t_game *game, t_point new)
{
	t_point	rc;

	rc.row = new.row / PX;
	rc.col = new.col / PX;
	if (game->map->map[rc.row][rc.col] == EXIT)
	{
		game->player->p_moves++;
		if (game->player->p_coins != game->t_coins)
		{
			ft_putendl_fd("You lack collectibles to leave 🔍", EXIT_SUCCESS);
			return ;
		}
		if (game->player->p_moves > game->max_moves)
		{
			ft_putendl_fd("You lost! 😞 Too many moves", EXIT_SUCCESS);
			free_mlx(game);
		}
		ft_putendl_fd("🎉🎉🎉 You won!, you're incredible! 🎉🎉🎉", EXIT_SUCCESS);
		free_mlx(game);
	}
}

static void	is_floor(t_game *game, t_point new)
{
	t_point	rc;

	rc.row = new.row / PX;
	rc.col = new.col / PX;
	if (game->map->map[rc.row][rc.col] == FLOOR)
		game->player->p_moves++;
}

int	update_pos_player(t_game *g, t_point new)
{
	if (g->player->row == g->p_exit.row && g->player->col == g->p_exit.col)
		g->map->map[g->p_exit.row][g->p_exit.col] = EXIT;
	else
		g->map->map[g->player->row][g->player->col] = FLOOR;
	is_coin(g, new);
	is_floor(g, new);
	is_exit(g, new);
	g->player->row = new.row / PX;
	g->player->col = new.col / PX;
	g->map->map[g->player->row][g->player->col] = PLAYER;
	return (1);
}
