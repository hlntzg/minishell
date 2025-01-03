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
	if (tmp->next) // Update the next node's previous pointer
		tmp->next->prev = tmp->prev;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	ms_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	if (!valid_builtin_args(cmd->args[1]))	
		return (ft_putendl_fd(ERR_UNSET_OPTIONS, STDERR_FILENO), EXIT_FAILURE);
	i = 1;
	while (cmd->args[i])
	{
		ms_handle_unset(data, cmd->args[i]);
		i++;
	}
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
