/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:19 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/24 00:28:15 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*==================================*/
void	is_rectangular(t_map *map)
{
	int	row;

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
/*==================================*/

/*==================================*/
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

void	is_surrounded_by_one(t_map *map, int lines)
{
	int	last;
	int	row;

	last = map->cols - 1;
	row = 0;
	if (check_up_do(map->map[0]) == 0 || check_up_do(map->map[lines - 1]) == 0)
	{
		free_matriz(&map->map);
		error_exit("The map must be surrounded by '1'");
	}
	while (row < lines)
	{
		if (!(map->map[row][0] == '1' && map->map[row][last] == '1'))
		{
			free_matriz(&map->map);
			error_exit("The map must be surrounded by '1'");
		}
		row++;
	}
}
/*==================================*/

/*==================================*/
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

void	check_items(t_game *game, int lines)
{
	int	c_count;
	int	p_count;
	int	e_count;
	int	row;

	c_count = 0;
	e_count = 0;
	p_count = 0;
	row = 1;
	while (row < lines - 1)
	{
		c_count += count_item(game->map->map[row], 'C');
		p_count += count_item(game->map->map[row], 'P');
		e_count += count_item(game->map->map[row], 'E');
		row++;
	}
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		free_matriz(&game->map->map);
		error_exit("Number of invalid items");
	}
	game->t_coins = c_count;
}
/*==================================*/

/*==================================*/
void	check_valid_items(t_map *map)
{
	int	row;
	int	col;

	row = 1;
	while (row < map->rows -1)
	{
		col = 0;
		while (map->map[row][col])
		{
			if (map->map[row][col] == '0')
			{
				col++;
				continue ;
			}
			else if (!ft_strchr("1PEC", map->map[row][col]))
			{
				free_matriz(&map->map);
				error_exit("Item not valid");
			}
			col++;
		}
		row++;
	}
}
/*==================================*/
/*==================================*/
static void get_pocision_of_p(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map->rows)
	{
		col = 0;
		while (col < game->map->cols)
		{
			if (game->map->map[row][col] == 'P')
			{
				game->player->pos_x = row;
				game->player->pos_y = col;
				row = game->map->rows;
				break ;
			}
			col++;
		}
		row++;
	}
}

static	int *create_a_map_copy(t_map *map)
{
	int	**matriz;
	int	row;

	matriz = ft_calloc(map->rows + 1, sizeof(int *));
	if (!matriz)
		return (NULL);
	row = 0;
	while (row < map->rows)
	{
		matriz[row] = ft_calloc(map->cols + 1, sizeof(int));
		if (!matriz[row])
			return (free_matriz_int(&matriz, map->rows), NULL);
		row++;
	}
	return (matriz);
}

void	check_accessibility(t_game *game)
{
	int	**visited;

	get_pocision_of_p(game);
	visited = create_a_map_copy(game->map);
	if (!visited)
		error_exit("An error occurred while checking the map access");
	visited[game->player->pos_x][game->player->pos_y] = 1;
	
}

/*==================================*/
/*==================================*/
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
	clean_map(game->map, lines);
	game->map->rows = lines;
	game->map->cols = ft_strlen(game->map->map[0]);
	is_rectangular(game->map);
	is_surrounded_by_one(game->map, lines);
	check_items(game, lines);
	check_valid_items(game->map);
	check_accessibility(game);
}
/*==================================*/