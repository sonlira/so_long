/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:20:53 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/16 21:20:54 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size1;
	size_t	size2;
	size_t	i;

	size1 = ft_strlen(dst);
	size2 = ft_strlen(src);
	if (size == 0)
		return (size2);
	if (size <= size1)
		return (size + size2);
	i = 0;
	while (src[i] != 0 && (size1 + i) < (size - 1))
	{
		dst[size1 + i] = src[i];
		i++;
	}
	dst[size1 + i] = 0;
	return (size1 + size2);
}
