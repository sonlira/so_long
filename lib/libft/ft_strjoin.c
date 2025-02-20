/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:11:57 by abaldelo          #+#    #+#             */
/*   Updated: 2024/10/10 19:00:08 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	copy_str(size_t i, size_t n, char *dst, char const *src)
{
	while (i < n && *src)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	total_size;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	total_size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	str = (char *) malloc(total_size * sizeof(char));
	if (!str)
		return (NULL);
	i = copy_str(i, total_size, str, s1);
	i = copy_str(i, total_size, str, s2);
	str[i] = '\0';
	return (str);
}
