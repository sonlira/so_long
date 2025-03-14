/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:00 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/09 18:02:00 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	free_mlx(game);
	exit(0);
	return (0);
}

static int	is_valid_move(t_game *game, t_point new)
{
	t_point	rc;

	rc.row = new.row / PX;
	rc.col = new.col / PX;
	if (game->map->map[rc.row][rc.col] == WALL)
	{
		ft_putendl_fd("❌ Maybe when you're a ghost 👻", 1);
		return (0);
	}
	return (1);
}

static void	print_date(t_game *game)
{
	ft_putendl_fd("+=======================================+", 1);
	ft_putendl_fd("+               SO_LONG                 +", 1);
	ft_putendl_fd("+=======================================+", 1);
	ft_putstr_fd("    * 👣 Maximum movement 👣: ", 1);
	ft_putnbr_fd(game->max_moves, 1);
	ft_putstr_fd("\n    * 👣 Your movements 👣: ", 1);
	ft_putnbr_fd(game->player->p_moves, 1);
	ft_putstr_fd("\n    * 💰 Missing collectibles 🍑: ", 1);
	ft_putnbr_fd(game->t_coins, 1);
	ft_putstr_fd("\n    * 💰 Collection items found 🍑: ", 1);
	ft_putnbr_fd(game->player->p_coins, 1);
	ft_putendl_fd("\n+=======================================+", 1);
	ft_putendl_fd("\n\n", 1);
}

int	key_press(int keycode, t_game *g)
{
	t_point	new;

	new.row = g->player->row * PX;
	new.col = g->player->col * PX;
	if (keycode == ESC_KEY)
		return (print_date(g), close_window(g), 0);
	else if (keycode == KEY_W)
		new.row -= PX;
	else if (keycode == KEY_S)
		new.row += PX;
	else if (keycode == KEY_A)
		new.col -= PX;
	else if (keycode == KEY_D)
		new.col += PX;
	else
		return (0);
	if (is_valid_move(g, new))
	{
		update_pos_player(g, new);
		mlx_clear_window(g->mlx, g->win);
		draw_map(g);
		print_date(g);
	}
	return (0);
}
