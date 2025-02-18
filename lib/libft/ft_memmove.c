/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                   	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:20:45 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/16 21:20:46 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (0);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (s < d && d < s + n)
	{
		s += n;
		d += n;
		while (n--)
			*(--d) = *(--s);
	}
	else
	{
		while (n--)
			*(d++) = *(s++);
	}
	return (dest);
}
