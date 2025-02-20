/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:16 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/20 22:05:50 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(void)
{
	exit (0);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*path_map;
	int		fd;
	int		lines;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <archivo.ber>", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	path_map = ft_strjoin("maps/", argv[1]);
	if (!path_map)
		return (EXIT_FAILURE);
	fd = open(path_map, O_RDONLY);
	printf("fd = %d path = %s\n", fd, path_map);
	if (fd == -1)
	{
		free(path_map);
		perror ("Error al abrir el archivo .ber ");
		return (EXIT_FAILURE);
	}
	lines = file_lines_ber(fd);
	close(fd);
	init_the_so_long(path_map, lines);
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
	return (EXIT_SUCCESS);
}
