/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:35:24 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/09 13:35:26 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_count(char *content)
{
    char	**split_tokens;
    int     total;
	int		j;

    split_tokens = ft_split(content, ' ');
    if (!split_tokens)
		return (0);
	total = 0;
	while (split_tokens[total])
		total++;
	if (split_tokens)
    {
	    j = 0;
        while (split_tokens[j])
            free(split_tokens[j++]);
        free(split_tokens);
    }
    return (total);
}


int count_expanded_args(t_token *tokens)
{
    int count;
    
    count = 0;
    while (tokens)
    {
        if (tokens->expand && has_space(tokens->content))
            count += expand_count(tokens->content);
        else
            count++;
        tokens = tokens->next;
    }
    return (count);
}