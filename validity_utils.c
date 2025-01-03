/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:25:47 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/09 10:25:48 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void quote_count(char *c, int *s_quote, int *d_quote) 
{
    if (*c == '\'')
        (*s_quote)++;
    else if (*c == '\"')
        (*d_quote)++;
}

int is_redirection(char *c)
{
    if (*c == '<' || *c == '>')
        return (1);
    return (0);
}