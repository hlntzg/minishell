/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:38:49 by nmeintje          #+#    #+#             */
/*   Updated: 2024/05/02 09:50:59 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int num)
{
	int	count;

	count = 0;
	if (num < 1)
		count++;
	while (num)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

static char	*new_ptr(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (0);
	return (str);
}

char	*ft_itoa(int n)
{
	long int	num;
	size_t		count;
	char		*string;

	num = n;
	count = count_size(n);
	if (n < 0)
		num *= -1;
	string = new_ptr(count);
	if (!string)
		return (0);
	*(string + count) = '\0';
	while (count--)
	{
		*(string + count) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(string + 0) = '-';
	return (string);
}
