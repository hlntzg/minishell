/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:00:03 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/19 15:28:55 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*src_char;
	char	*dst_char;

	src_char = (char *)src;
	dst_char = (char *)dst;
	if (!dst && !src)
		return (dst);
	while (n--)
	{
		*dst_char++ = *src_char++;
	}
	return (dst);
}
