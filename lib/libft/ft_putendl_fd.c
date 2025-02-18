/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:54:52 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/25 16:54:53 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	while (*s != 0)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
