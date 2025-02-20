/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:19 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/20 21:22:05 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_game *game, char *file, int size)
{
	int	i;
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Error al abrir el archivo .ber");
	game->map =ft_calloc(size + 1, sizeof(char *));
	if (!game->map)
		error_exit("Fallo al reservar memoria para el mapa");
	i = 0;
	while (i < size)
	{
		game->map[i] = get_next_line(fd);
		if (!game->map[i])
		{
			free_matriz(&game->map);
			error_exit("Fallo al reservar memoria para el mapa");
		}
		i++;
	}
	close(fd);
}
