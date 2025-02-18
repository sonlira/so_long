/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:16 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/18 22:52:31 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void)
{
	exit (0);
	return (0);
}

// void init_map(t_game *game)
// {
//     game->map[0] = "111111";
//     game->map[1] = "1000E1";
//     game->map[2] = "10P001";
//     game->map[3] = "1000C1";
//     game->map[4] = "111111";
// }


int	main(void)
{
	t_game game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 240, 200, "So_long");
	game.img = mlx_xpm_file_to_image(game.mlx, "assets/player.xpm", &(int){40}, &(int){40});
	game.img_x = 80;
	game.img_y = 80;

	init_map(&game);

	mlx_put_image_to_window(game.mlx, game.win, game.img, game.img_x, game.img_y);
	mlx_hook(game.win, ON_DESTROY, 0, close_window, NULL);
	mlx_key_hook(game.win, key_press, &game);


	mlx_loop(game.mlx);
	return (0);
}
