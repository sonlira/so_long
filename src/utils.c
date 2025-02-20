/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:28 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/20 19:38:41 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *msg)
{
	perror(msg);
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
