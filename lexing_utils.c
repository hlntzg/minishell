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
		return (NULL); // can make this an error later if necessary
	new->type = type;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	add_tokens(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!token || !new)
		return ;
	if (!(*token))
	{
		*token = new;
		new->next = NULL;
		return ;
	}
	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(char *src, int size)
{
	int		i;
	char	*dup;

	i = size + 1;
	dup = (char *)malloc(i * sizeof (char));
	if (dup == NULL)
		return (NULL);
	ft_strcpy(dup, src);
	return (dup);
}