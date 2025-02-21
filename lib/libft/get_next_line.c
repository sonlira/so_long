/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:35:57 by abaldelo          #+#    #+#             */
/*   Updated: 2025/02/21 18:13:42 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_buffer(int fd, char *buffer, char *store)
{
	char	*tmp;
	ssize_t	read_bytes;

	tmp = NULL;
	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (!store)
			store = ft_strdup("");
		tmp = ft_strjoin(store, buffer);
		free(store);
		store = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*store;
	char		*line;
	char		*line_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, buffer, store);
	if (!line)
		return (free(store), store = NULL, NULL);
	line_pos = ft_strchr(line, '\n');
	if (line_pos && line_pos[1] != '\0')
	{
		store = ft_strdup(line_pos + 1);
		line_pos[1] = '\0';
	}
	else
		store = NULL;
	return (line);
}
