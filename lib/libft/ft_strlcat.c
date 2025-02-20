/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:16:54 by abaldelo          #+#    #+#             */
/*   Updated: 2024/10/08 19:57:17 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l_dst;
	size_t	l_src;
	size_t	i;

	l_dst = ft_strlen(dst);
	l_src = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (l_src);
	if (size <= l_dst)
		return (l_src += size);
	else
		l_src += l_dst;
	while (src[i] != '\0' && l_dst < (size - 1) && dst != src)
	{
		dst[l_dst] = src[i];
		l_dst++;
		i++;
	}
	dst[l_dst] = '\0';
	return (l_src);
}
