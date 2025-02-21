/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:28 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 15:12:07 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *msg)
{
	// perror(msg);
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
