/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:25 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/03 00:28:55 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *g)
{
	int	r;
	int	c;

	r = 0;
	while (g->map->map[r])
	{
		c = 0;
		while (g->map->map[r][c])
		{
			if (g->map->map[r][c] == WALL)
				mlx_put_image_to_window(g->mlx, g->win, g->w, c * PX, r * PX);
			else if (g->map->map[r][c] == FLOOR)
				mlx_put_image_to_window(g->mlx, g->win, g->f, c * PX, r * PX);
			else if (g->map->map[r][c] == PLAYER)
				mlx_put_image_to_window(g->mlx, g->win, g->p, c * PX, r * PX);
			else if (g->map->map[r][c] == COIN)
				mlx_put_image_to_window(g->mlx, g->win, g->c, c * PX, r * PX);
			else if (g->map->map[r][c] == EXIT)
				mlx_put_image_to_window(g->mlx, g->win, g->e, c * PX, r * PX);
			c++;
		}
		r++;
	}
}
