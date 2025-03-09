/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:09 by abaldelo          #+#    #+#             */
/*   Updated: 2025/03/09 18:02:02 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_matriz(char ***matriz)
{
	int	i;

	i = 0;
	if (!matriz || !*matriz)
		return ;
	while ((*matriz)[i])
	{
		free((*matriz)[i]);
		i++;
	}
	free(*matriz);
	*matriz = NULL;
}

void	free_matriz_int(int ***matriz, size_t size)
{
	size_t	i;

	i = 0;
	if (!matriz || !*matriz)
		return ;
	while (i < size)
	{
		free((*matriz)[i]);
		i++;
	}
	free(*matriz);
	*matriz = NULL;
}

void	free_matriz_point(t_point ***matriz, size_t size)
{
	size_t	i;

	i = 0;
	if (!matriz || !*matriz)
		return ;
	while (i < size)
	{
		free((*matriz)[i]);
		i++;
	}
	free(*matriz);
	*matriz = NULL;
}

void	free_queue(t_queue *queue)
{
	if (!queue->points)
		return ;
	free(queue->points);
	free(queue);
}

void	free_mlx(t_game *game)
{
	if (!game)
		error_exit("game not initialized");
	if (game->map->map)
		free_matriz(&game->map->map);
	if (game->rute)
		free(game->rute);
	if (game->w)
		mlx_destroy_image(game->mlx, game->w);
	if (game->f)
		mlx_destroy_image(game->mlx, game->f);
	if (game->p)
		mlx_destroy_image(game->mlx, game->p);
	if (game->c)
		mlx_destroy_image(game->mlx, game->c);
	if (game->e)
		mlx_destroy_image(game->mlx, game->e);
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_putendl_fd("game closed!!!", 1);
}
