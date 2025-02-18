/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:56:09 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/25 16:56:10 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_check(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		finish;
	size_t		i;
	char		*result;

	start = 0;
	while (s1[start] && ft_check(s1[start], set))
		start++;
	finish = ft_strlen(s1);
	while (finish > start && ft_check(s1[finish - 1], set))
		finish--;
	result = (char *)malloc(finish - start + 1);
	if (result == 0)
		return (0);
	i = 0;
	while (start < finish)
		result[i++] = s1[start++];
	result[i] = 0;
	return (result);
}
