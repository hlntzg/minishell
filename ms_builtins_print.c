/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:45:55 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/05 11:57:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

static int	env_cmp_key(t_env *a, t_env *b)
{
	if (a == NULL || b == NULL || a->key == NULL || b->key == NULL)
		return (0);
	return (ft_strcmp(a->key, b->key) > 0);
}

// Sort the t_env linked list based on the 'key' field
t_env	*env_sort_list(t_env *lst, int (*cmp)(t_env *, t_env *))
{
	t_env	*tmp;
	char	*temp_key;
	char	*temp_value;

	tmp = lst;
	while (tmp && tmp->next)
	{
		if (cmp(tmp, tmp->next))
		{
			temp_key = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = temp_key;
			temp_value = tmp->value;
			tmp->value = tmp->next->value;
			tmp->next->value = temp_value;
			tmp = lst;
		}
		else
			tmp = tmp->next;
	}
	return (lst);
}

void	builtins_print_export_variables(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = env_sort_list(data->env, env_cmp_key);
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		if (!tmp->value)
			ft_putendl_fd(tmp->key, fd);
		else
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putendl_fd("\"", fd);
		}
		tmp = tmp->next;
	}
}
