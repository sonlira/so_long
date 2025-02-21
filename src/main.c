/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:16 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 15:09:15 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	*map_path;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <file.ber>", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	map_path = ft_strjoin("maps/", argv[1]);
	if (!map_path)
		return (EXIT_FAILURE);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		free(map_path);
		perror ("Error opening the file");
		return (EXIT_FAILURE);
	}
	init_the_so_long(map_path, file_lines_ber(fd));
	return (EXIT_SUCCESS);
}

/////////
	// t_game game;

	// game.mlx = mlx_init();
	// game.win = mlx_new_window(game.mlx, 240, 200, "So_long");
	// game.img = mlx_xpm_file_to_image(game.mlx, "assets/player.xpm", &(int){40}, &(int){40});
	// game.img_x = 80;
	// game.img_y = 80;
	// // init_map(&game);

	// mlx_put_image_to_window(game.mlx, game.win, game.img, game.img_x, game.img_y);
	// mlx_hook(game.win, ON_DESTROY, 0, close_window, NULL);
	// mlx_key_hook(game.win, key_press, &game);


	// mlx_loop(game.mlx);
