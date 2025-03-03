/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/03 01:48:51 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_images(t_game *g)
{
	int		w;
	int		h;

	w = PX;
	h = PX;
	g->w = mlx_xpm_file_to_image(g->mlx, "assets/1.xpm", &w, &h);
	if (!g->w)
		return (0);
	g->f = mlx_xpm_file_to_image(g->mlx, "assets/0.xpm", &w, &h);
	if (!g->f)
		return (0);
	g->p = mlx_xpm_file_to_image(g->mlx, "assets/p.xpm", &w, &h);
	if (!g->p)
		return (0);
	g->c = mlx_xpm_file_to_image(g->mlx, "assets/c.xpm", &w, &h);
	if (!g->c)
		return (0);
	g->e = mlx_xpm_file_to_image(g->mlx, "assets/e.xpm", &w, &h);
	if (!g->e)
		return (0);
	return (1);
}

static void	start_mlx(t_game *g)
{
	t_map	*map;

	map = g->map;
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		free_mlx(g);
		error_exit("Failed to init mlx");
	}
	g->win = mlx_new_window(g->mlx, map->cols * PX, map->rows * PX, "SO_LONG");
	if (!g->win)
	{
		free_mlx(g);
		error_exit("Failed to init win");
	}
	if (!load_images(g))
	{
		free_mlx(g);
		error_exit("Failed to load images");
	}
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
