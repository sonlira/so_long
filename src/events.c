/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:00 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 14:43:28 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void)
{
	exit (0);
	return (0);
}

int is_valid_move(t_game *game, int new_x, int new_y)
{
    int grid_x = new_x / PIXEL;
    int grid_y = new_y / PIXEL;

	if (game->map[grid_y][grid_x] == '1')
	{
		printf("❌ NO puedes pasar una pared\n");
		return (0);
	}
	if (game->map[grid_y][grid_x] == 'C')
	{
		printf("💰 Recogiste una monedita\n");
        game->map[grid_y][grid_x] = '0';

	}
	if (game->map[grid_y][grid_x] == 'E')
	{
		printf("🎉 Llegaste a la salida, ¡ganaste!\n");
        exit(0);
	}
    return (1);
}

int	key_press(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->img_x;
	new_y = game->img_y;
	if (keycode == ESC_KEY)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_W)
		new_y -= PIXEL;
	else if (keycode == KEY_S)
		new_y += PIXEL;
	else if (keycode == KEY_A)
		new_x -= PIXEL;
	else if (keycode == KEY_D)
		new_x += PIXEL;
	if (is_valid_move(game, new_x, new_y))
	{
		game->img_x = new_x;
		game->img_y = new_y;
		mlx_clear_window(game->mlx, game->win);
		mlx_put_image_to_window(game->mlx, game->win, game->img, game->img_x, game->img_y);
	}
	printf("x = %d, y = %d\n", game->img_x, game->img_y);
	return (0);
}
