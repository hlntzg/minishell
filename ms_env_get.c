/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:43:48 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/10 16:44:10 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	env_get_key(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*env_get_node(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*env_get_value(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
