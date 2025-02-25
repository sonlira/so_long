/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:34:58 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/25 22:56:52 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_up_do(char *row)
{
	int	col;

	col = 0;
	while (row[col])
	{
		if (row[col] != WALL)
			return (0);
		col++;
	}
	return (1);
}

void	check_one_on_edges(t_map *map, int lines)
{
	int	last;
	int	row;

	if (!map || lines <= 2)
		return ;
	last = map->cols - 1;
	row = 0;
	if (check_up_do(map->map[0]) == 0 || check_up_do(map->map[lines - 1]) == 0)
	{
		free_matriz(&map->map);
		error_exit("The map must be surrounded by '1'");
	}
	while (row < lines)
	{
		if (!(map->map[row][0] == WALL && map->map[row][last] == WALL))
		{
			free_matriz(&map->map);
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
		if (row[col] == FLOOR)
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

	if (!game || lines <= 2)
		return ;
	c_count = 0;
	e_count = 0;
	p_count = 0;
	row = 1;
	while (row < lines - 1)
	{
		c_count += count_item(game->map->map[row], COIN);
		p_count += count_item(game->map->map[row], PLAYER);
		e_count += count_item(game->map->map[row], EXIT);
		row++;
	}
	if (p_count != 1 || e_count != 1 || c_count < 1)
	{
		free_matriz(&game->map->map);
		error_exit("Number of invalid items");
	}
	game->t_coins = c_count;
}

void	check_valid_items(t_map *map)
{
	int	row;
	int	col;

	if (!map)
		return ;
	row = 1;
	while (row < map->rows -1)
	{
		col = 0;
		while (map->map[row][col])
		{
			if (map->map[row][col] == FLOOR)
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
