/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                   :+:      :+:    :+:   */
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

char	*ft_strrchr(const char *c, int n)
{
	size_t	i;

	i = ft_strlen(c);
	while (i > 0)
	{
		if (c[i] == (char)n)
			return ((char *)c + i);
		i--;
	}
	if (c[0] == (char)n)
		return ((char *)c);
	return (0);
}
