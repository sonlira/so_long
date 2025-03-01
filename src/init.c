/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/02 00:27:41 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_mlx(t_game *g)
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
	mlx_loop(g->mlx);
}

void	init_the_so_long(char *file, int lines)
{
	t_game	game;
	t_map	map;
	t_play	player;

	game.map = &map;
	game.player = &player;
	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, 800, 600, "so_long");
	init_map(&game, file, lines);
	if (!find_the_shortest_way(&game))
		error_exit("Failed to find the best route");
	printf("max_moves: %d\n",game.max_moves);
	start_mlx(&game);
	free_matriz(&game.map->map);
	free(game.rute);
	// mlx_loop(game.mlx);
}
