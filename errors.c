/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:50:18 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/09 12:50:20 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//some rror functions maybe. or maybe I'll delete this if it turns out
// we don't need it.

int ft_error(void)
{
    printf("Lexical error in input.\n");
    exit(EXIT_FAILURE);
}

/*void    free_data(char *str)
{
    
}*/