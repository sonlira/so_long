/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:00 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/02 20:07:53 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	// free_matriz(&game->map->map);
	// free(game->rute);
	free_mlx(game);
	exit (0);
	return (0);
}

int	is_valid_move(t_game *game, t_point new)
{
	t_point	rc;

	rc.row = floor((double)new.row / PX);
	rc.col = floor((double)new.col / PX);

	printf("new col = %d, new row = %d\n", new.col, new.row);
	printf("rc col = %d, rc row = %d\n", rc.col, rc.row);
	if (game->map->map[rc.row][rc.col] == WALL)
	{
		printf("❌ NO puedes pasar una pared\n");
		return (0);
	}
	if (game->map->map[rc.row][rc.col] == COIN)
	{
		printf("💰 Recogiste unas moneditas\n");
        // game->map->map[rc.row][rc.col] = '0';

	}
	if (game->map->map[rc.row][rc.col] == EXIT)
	{
		printf("🎉 Llegaste a la salida, ¡ganaste!\n");
        // exit(0);
	}
    return (1);
}

int	key_press(int keycode, t_game *g)
{
	t_point	new;

	new.row = g->player->row * 65;
	new.col = g->player->col * 65;
	if (keycode == ESC_KEY)
		close_window(g);
	else if (keycode == KEY_W)
		new.row -= PX;
	else if (keycode == KEY_S)
		new.row += PX;
	else if (keycode == KEY_A)
		new.col -= PX;
	else if (keycode == KEY_D)
		new.col += PX;
	if (is_valid_move(g, new))
	{
		g->map->map[g->player->row][g->player->col] = FLOOR;
		g->player->row = floor((double)new.row / PX);
		g->player->col = floor((double)new.col / PX);
		g->map->map[g->player->row][g->player->col] = PLAYER;
		mlx_clear_window(g->mlx, g->win);
		draw_map(g);
		// mlx_put_image_to_window(g->mlx, g->win, g->p, g->player->col * PX, g->player->row * PX);
	}
	printf("col = %d, row = %d\n", g->player->col, g->player->row);
	return (0);
}
