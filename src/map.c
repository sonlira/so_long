/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:19 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 23:04:23 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_rectangular(t_game *game)
{
	size_t	col;
	size_t	row;

	col = ft_strlen(game->map->map[0]);
	row = 1;
	while (game->map->map[row])
	{
		if (ft_strlen(game->map->map[row]) != col)
		{
			free_matriz(&game->map->map);
			error_exit("Map is not valid, not is rectangular");
		}
		row++;
	}
}

static int	check_up_do(char *row)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (row[col] != '1')
			return (0);
		col++;
	}
	return (1);
}

void	is_surrounded_by_one(t_game *game, int len)
{
	int	last;
	int	row;

	last = ft_strlen(game->map->map[0]) - 1;
	row = 0;
	if (check_up_do(game->map->map[0]) == 0 || check_up_do(game->map->map[len - 1]) == 0)
	{
		free_matriz(&game->map);
		error_exit("The map must be surrounded by '1'");
	}
	while (row < len)
	{
		if (!(game->map->map[row][0] == '1' && game->map->map[row][last] == '1'))
		{
			free_matriz(&game->map);
			error_exit("The map must be surrounded by '1'");
		}
		row++;
	}
}

static int	count_item(char *row, char item)
{
	int	col;
	int	count;

	col = 0;
	count = 0;
	while (row[col])
	{
		if (row[col] == '0')
		{
			col++;
			continue ;
		}
		else if (row[col] == item)
			count++;
		col++;
	}
	return (count);
}

void	check_items(t_game *game, int len)
{
	int	c_count;
	int	p_count;
	int	e_count;
	int	row;

	c_count = 0;
	e_count = 0;
	p_count = 0;
	row = 1;
	while (row < len - 1)
	{
		c_count += count_item(game->map[row], 'C');
		p_count += count_item(game->map[row], 'P');
		e_count += count_item(game->map[row], 'E');
		row++;
	}
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		free_matriz(&game->map);
		error_exit("Number of invalid items");
	}
	game->coins = c_count;
}

void	check_valid_items(t_game *game, int len)
{
	int	row;
	int	col;

	row = 1;
	while (row < len - 1)
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == '0')
			{
				col++;
				continue ;
			}
			else if (!ft_strchr("1PEC", game->map[row][col]))
			{
				free_matriz(&game->map);
				error_exit("Item not valid");
			}
			col++;
		}
		row++;
	}
}

static void	clean_map(t_game *game, int lines)
{
	int		row;
	char	*line;

	row = 0;
	while (row < lines)
	{
		line = ft_strrchr(game->map->map[row], '\n');
		if (line)
			line[0] = '\0';
		row++;
	}
}

void	init_map(t_game *game, char *file, int lines)
{
	int	i;
	int	fd;

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
	clean_map(game, lines);
	is_rectangular(game);
	is_surrounded_by_one(game, lines);
	check_items(game, lines);
	check_valid_items(game, lines);
}
