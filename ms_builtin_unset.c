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
