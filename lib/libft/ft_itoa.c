/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kegonzal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:54:15 by kegonzal          #+#    #+#             */
/*   Updated: 2024/09/25 16:54:16 by kegonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_fill(size_t size, char *str, long n)
{
	*(str + size--) = 0;
	while (n > 0)
	{
		*(str + size) = n % 10 + '0';
		n /= 10;
		size--;
	}
	if (size == 0 && str[1] == 0)
		*(str + size) = '0';
	else if (size == 0 && str[1] != 0)
		*(str + size) = '-';
}

char	*ft_itoa(int n)
{
	char	*result;
	long	new;
	size_t	size;

	size = 0;
	new = n;
	if (n <= 0)
	{
		new *= -1;
		size = 1;
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	result = (char *)malloc(size + 1);
	if (result == 0)
		return (0);
	ft_fill(size, result, new);
	return (result);
}
