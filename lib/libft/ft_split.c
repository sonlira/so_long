/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:04:35 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/20 15:04:36 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s != 0)
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

static char	*ft_char(const char *str, int start, int finish, char **matrix)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
	{
		while (matrix[i] != 0)
			free(matrix[i++]);
		free(matrix);
		return (0);
	}
	while (start < finish)
		word[i++] = str[start++];
	word[i] = 0;
	return (word);
}

static int	ft_fill_matrix(const char *s, char c, char **matrix)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		index;
	char	*new;

	i = -1;
	j = 0;
	index = -1;
	len = ft_strlen(s);
	while (++i <= len)
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == len) && index >= 0)
		{
			new = ft_char(s, index, i, matrix);
			if (!new)
				return (0);
			matrix[j++] = new;
			index = -1;
		}
	}
	matrix[j] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = ft_calloc((ft_words(s, c) + 1), sizeof(char *));
	if (!result || !s)
		return (0);
	if (!ft_fill_matrix(s, c, result))
		return (0);
	return (result);
}
