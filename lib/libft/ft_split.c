/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:53:59 by abaldelo          #+#    #+#             */
/*   Updated: 2024/10/19 22:34:45 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	length_word(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	return (size);
}

static	size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += length_word(s, c);
		}
		else
			s++;
	}
	return (count);
}

static	void	free_mem(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	ntwords;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	ntwords = count_words(s, c);
	words = (char **)malloc((ntwords + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			words[i] = ft_substr(s, 0, length_word(s, c));
			if (!words[i++])
				return (free_mem(words), NULL);
			s += length_word(s, c);
		}
		else
			s++;
	}
	words[i] = NULL;
	return (words);
}
