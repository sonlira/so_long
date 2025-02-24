/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:09 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/24 18:18:15 by abaldelo         ###   ########.fr       */
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

void	free_queue(t_queue *q)
{
	if (!q->points)
		return ;
	free(q->points);
	free(q);
}