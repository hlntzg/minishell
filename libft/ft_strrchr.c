/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:42:43 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/26 15:28:19 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int c)
{
	const char	*sub;

	sub = 0;
	while (*str)
	{
		if (*str == (char)c)
			sub = str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return ((char *)sub);
}
