/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:16 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/07 17:51:21 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_valid_file(char *file)
{
	char	*extent;

	extent = ft_strrchr(file, '.');
	if (ft_strlen(file) == ft_strlen(".ber"))
		error_exit("Extension of invalid file");
	else if (!ft_memcmp(file, "..ber", ft_strlen("..ber")))
		error_exit("Extension of invalid file");
	else if (!extent || ft_memcmp(extent, ".ber", ft_strlen(".ber")) != 0)
		error_exit("Extension of invalid file");
}

int	main(int argc, char **argv)
{
	char	*map_path;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./so_long <file.ber>", 2);
		return (EXIT_FAILURE);
	}
	is_valid_file(argv[1]);
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
