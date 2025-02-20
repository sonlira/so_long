/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaldelo <abaldelo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:10:02 by abaldelo          #+#    #+#             */
/*   Updated: 2024/10/08 19:58:30 by abaldelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr_d;
	const unsigned char	*ptr_s;

	ptr_d = (unsigned char *)dest;
	ptr_s = (const unsigned char *)src;
	i = 0;
	if (!ptr_d && !ptr_s)
		return (NULL);
	if (ptr_s < ptr_d)
	{
		while (n--)
			ptr_d[n] = ptr_s[n];
	}
	else
	{
		while (i < n)
		{
			ptr_d[i] = ptr_s[i];
			i++;
		}
	}
	return (dest);
}
