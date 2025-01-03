/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:22:02 by nmeintje          #+#    #+#             */
/*   Updated: 2024/12/04 16:22:08 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_type type, char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

void	add_tokens(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (!(*token))
	{
		*token = new;
		new->next = NULL;
	}
	else
	{
		temp = *token;
		if (!temp)
			return ;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

char	*ft_strndup(char *src, int size)
{
	int		i;
	int		j;
	char	*dup;

	i = size + 1;
	dup = (char *)malloc(i * sizeof(char));
	if (dup == NULL)
		return (NULL);
	j = 0;
	while (j < size && src[j] != '\0')
	{
		dup[j] = src[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

void free_tokens(t_token *token)
{
    t_token *temp;

    while (token)
    {
        temp = token->next; // Save the next token
        if (token->content)
            free(token->content); // Free the token's content
        free(token); // Free the token itself
        token = temp; // Move to the next token
    }
}