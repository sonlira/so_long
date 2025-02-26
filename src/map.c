/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:19 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/26 00:31:17 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_pocision_of_p(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map->rows)
	{
		col = 0;
		while (col < game->map->cols)
		{
			if (game->map->map[row][col] == PLAYER)
			{
				game->player->row = row;
				game->player->col = col;
				row = game->map->rows;
				break ;
			}
			col++;
		}
		row++;
	}
}

void	init_map(t_game *game, char *file, int lines)
{
	if (lines <= 2)
		error_exit("Map is not valid.");
	create_map(game, file, lines);
	game->map->rows = lines;
	game->map->cols = ft_strlen(game->map->map[0]);
	get_pocision_of_p(game);
	check_rectangular_shape(game->map);
	check_one_on_edges(game->map, lines);
	check_items(game, lines);
	check_valid_items(game->map);
	check_accessibility(game);
}
