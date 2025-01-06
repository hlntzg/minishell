#include "./includes/ms.h"
/*
int	set_redirections(t_data *data, t_cmd *cmd, t_token *tmp)
{
	if (tmp->type == REDIN)
	{
		cmd->infile = open(tmp->next->value, O_RDONLY);
		if (cmd->infile == -1)
			return (ms_error(tmp->next->value, NULL, 1, FAILURE));
	}
	else if (tmp->type == HEREDOC)
		return (ms_set_heredoc(data, cmd, tmp));
	if (tmp->type == REDOUT_T)
	{
		cmd->outfile_t = open(tmp->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->outfile_t == -1)
			return (ms_error(tmp->next->value, NULL, 1, FAILURE));
	}
	else if (tmp->type == REDOUT_A)
	{
		cmd->outfile_a = open(tmp->next->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->outfile_a == -1)
			return (ms_error(tmp->next->value, NULL, 1, FAILURE));
	}
	return (SUCCESS);
}
*/
int	ms_pre_exe_newline(t_data *data)
{
	data->envp = env_get_array_str(data);
	if (!data->envp)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	data->envp_path = exe_get_path(data->envp);
	if (!data->envp_path)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	data->pid = malloc(sizeof(int) * data->total_cmds);
	if (!data->pid)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	data->fd = malloc(sizeof(int) * (2 * (data->total_cmds - 1))); // total_cmds - 1 = total_process ??? -->  process is the pipe count 
	if (!data->fd)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));

//	need to be update for an array of commands
//	if (set_redirections(data, cmd) != SUCCESS)
//		return (FAILURE);
	return (SUCCESS);
}
