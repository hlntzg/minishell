/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:30:45 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/05 11:30:47 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

static void	ms_handle_unset(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = env_get_node(data, key);
	if (!tmp)
		return ;
	if (!tmp->prev)
		data->env = tmp->next;
	else
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	ms_unset(t_data *data, char **_cmd)
{
	int	i;

	if (!_cmd[1])
		return (SUCCESS);
	if (_cmd[1] && !valid_builtin_args(_cmd[1]))
	{
		data->exit_code = 2;
		return (ft_putendl_fd(ERR_UNSET_OPTIONS, STDERR_FILENO), EXIT_FAILURE);
	}
	i = 1;
	while (_cmd[i])
	{
		ms_handle_unset(data, _cmd[i]);
		i++;
	}
	return (SUCCESS);
}
