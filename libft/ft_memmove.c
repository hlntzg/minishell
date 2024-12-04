/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:45:08 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/25 18:47:08 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_char;
	char	*dst_char;

	src_char = (char *)src;
	dst_char = (char *)dst;
	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		while (len--)
			*dst_char++ = *src_char++;
	}
	else if (dst > src)
	{
		dst_char += len - 1;
		src_char += len - 1;
		while (len--)
			*dst_char-- = *src_char--;
	}
	return (dst);
}
