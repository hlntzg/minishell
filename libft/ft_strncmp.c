/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:43:44 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/25 18:23:30 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
    unsigned int    n;

    n = 0;
    while (s1[n] == s2[n])
    {
        if (s1[n] == '\0' || s2[n] == '\0')
            break ;
        n++;
    }
    if (s1[n] == '\0' && s2[n] == '\0')
        return (0);
    else
        return (s1[n] - s2[n]);
}

