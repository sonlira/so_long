/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:28 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/28 21:28:38 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *msg)
{
	ft_putendl_fd("Error", EXIT_FAILURE);
	ft_putendl_fd((char *)msg, EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

int	file_lines_ber(int fd)
{
	int		count_line;
	char	*line;

	count_line = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			count_line++;
			free(line);
		}
		else
			break ;
	}
	close(fd);
	return (count_line);
}

t_queue	*create_queue(int size)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->points = malloc(sizeof(t_point) * size);
	if (!queue->points)
		return (free(queue), NULL);
	queue->front = 0;
	queue->final = 0;
	queue->c_coins = 0;
	queue->with_exit = 0;
	queue->size = size;
	return (queue);
}

void	enqueue(t_queue *queue, int row, int col)
{
	if (queue->final == queue->size)
		return ;
	queue->points[queue->final].row = row;
	queue->points[queue->final].col = col;
	queue->final++;
}

t_point	dequeue(t_queue *queue)
{
	t_point	point;

	point.col = -1;
	point.row = -1;
	if (queue->front == queue->final)
		return (point);
	point = queue->points[queue->front];
	queue->front++;
	return (point);
}
