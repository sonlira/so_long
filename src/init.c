/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 23:33:42 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_the_so_long(char *file, int lines)
{
	t_game	game;
	t_map	map;
	game.map = &map;
	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, 800, 600, "so_long");
	if (lines <= 2)
		error_exit("Map is not valid.");
	init_map(&game, file, lines);
	free_matriz(&game.map->map);
	// mlx_loop(game.mlx);
}
