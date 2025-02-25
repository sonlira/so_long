/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:18:51 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/25 22:59:30 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	**start_matriz_int(t_map *map, int number)
{
	int	**matriz;
	int	row;
	int	col;

	if (!map)
		return (NULL);
	matriz = ft_calloc(map->rows + 1, sizeof(int *));
	if (!matriz)
		return (NULL);
	row = 0;
	while (row < map->rows)
	{
		matriz[row] = ft_calloc(map->cols + 1, sizeof(int));
		if (!matriz[row])
			return (free_matriz_int(&matriz, map->rows), NULL);
		col = 0;
		while (number != 0 && col < map->cols)
		{
			matriz[row][col] = number;
			col++;
		}
		row++;
	}
	return (matriz);
}

static void	clean_map(t_map *map, int lines)
{
	int		row;
	char	*line;

	row = 0;
	while (row < lines -1)
	{
		line = ft_strrchr(map->map[row], '\n');
		if (line)
			line[0] = '\0';
		row++;
	}
}

void	create_map(t_game *game, char *file, int lines)
{
	int	i;
	int	fd;

	if (!game || !file || lines <= 2)
		return ;
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		error_exit("Error opening the file");
	game->map->map = ft_calloc(lines + 1, sizeof(char *));
	if (!game->map)
		error_exit("Failed to reserve memory for map");
	i = 0;
	while (i < lines)
	{
		game->map->map[i] = get_next_line(fd);
		if (!game->map->map[i])
		{
			free_matriz(&game->map->map);
			error_exit("Failed to reserve memory for map");
		}
		i++;
	}
	close(fd);
	clean_map(game->map, lines);
}

void	check_rectangular_shape(t_map *map)
{
	int	row;

	if (!map)
		return ;
	row = 1;
	while (map->map[row])
	{
		if ((int)ft_strlen(map->map[row]) != map->cols)
		{
			free_matriz(&map->map);
			error_exit("Map is not valid, not is rectangular");
		}
		row++;
	}
}
