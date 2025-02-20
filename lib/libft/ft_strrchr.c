/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:05:06 by abaldelo          #+#    #+#             */
/*   Updated: 2024/10/08 19:58:09 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	longer;

	longer = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + longer);
	while (longer--)
	{
		if (s[longer] == (char)c)
			return ((char *)s + longer);
	}
	return (NULL);
}
