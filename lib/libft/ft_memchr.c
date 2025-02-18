/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:36:40 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/17 20:36:41 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;

	s = (const unsigned char *) src;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char) c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
