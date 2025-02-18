/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:52:09 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/10 16:52:10 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

t_env	*env_lstnew(char *key, char *value)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = env_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

void	env_add_new(t_data *data, char *key, char *value)
{
	t_env	*new;

	new = env_lstnew(key, value);
	if (!new)
		return ;
	env_lstadd_back(&data->env, new);
}

int	env_lstsize(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{	
		tmp = tmp->next;
		i++;
	}
	return (i);
}
