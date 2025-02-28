/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/28 20:55:21 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	free_matriz(&game.map->map);
	free(game.rute);
	// mlx_loop(game.mlx);
}
