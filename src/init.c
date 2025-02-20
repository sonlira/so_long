/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:12 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/20 21:47:14 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_the_so_long(char *file, int size)
{
	t_game	game;

	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, 800, 600, "so_long");
	init_map(&game, file, size);
	free_matriz(&game.map);
	// mlx_loop(game.mlx);
}
