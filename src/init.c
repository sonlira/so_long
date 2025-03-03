/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/03 01:09:01 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	start_mlx(t_game *g)
{
	int		w;
	int		h;
	t_map	*map;

	w = PX;
	h = PX;
	map = g->map;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, map->cols * PX, map->rows * PX, "SO_LONG");
	g->w = mlx_xpm_file_to_image(g->mlx, "assets/1.xpm", &w, &h);
	g->f = mlx_xpm_file_to_image(g->mlx, "assets/0.xpm", &w, &h);
	g->p = mlx_xpm_file_to_image(g->mlx, "assets/p.xpm", &w, &h);
	g->c = mlx_xpm_file_to_image(g->mlx, "assets/c.xpm", &w, &h);
	g->e = mlx_xpm_file_to_image(g->mlx, "assets/e.xpm", &w, &h);
	draw_map(g);
	mlx_hook(g->win, ON_DESTROY, 0, close_window, g);
	mlx_key_hook(g->win, key_press, g);
	mlx_loop(g->mlx);
}

void	init_the_so_long(char *file, int lines)
{
	t_game	game;
	t_map	map;
	t_play	player;

	game.map = &map;
	game.player = &player;
	init_map(&game, file, lines);
	if (!find_the_shortest_way(&game))
		error_exit("Failed to find the best route");
	start_mlx(&game);
}
