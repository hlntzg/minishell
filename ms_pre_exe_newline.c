#include "./includes/ms.h"

void	exe_get_total_redirections_and_pipes(t_data *data, t_tree_node *ast)
{
	if (ast->type == PIPE)
		data->count_pipe += 1;
	else if (ast->type == REDIN || ast->type == HEREDOC)
		data->count_infile += 1;
	else if (ast->type == REDOUT_A ||ast->type == REDOUT_T)
		data->count_outfile += 1;
	if (ast->left)
		exe_get_total_redirections_and_pipes(data, ast->left);
	if (ast->right)
		exe_get_total_redirections_and_pipes(data, ast->right);
	if (data->count_pipe)
		data->processes = data->count_pipe + 1;
//	else
//		data->processes = 1;
}

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
//	data->fd = malloc(sizeof(int) * (2 * (data->total_cmds - 1))); // total_cmds - 1 = total_process ??? -->  process is the pipe count 
//	if (!data->fd)
//		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	
	data->count_infile = 0;
	data->count_outfile = 0;
	data->count_pipe = 0;
	data->redirect_input = 0;
	data->redirect_output = 0;
//	data->executed_pipe = 0;
	data->processes = 0;
//	data->count_child = 0;
	data->fd[0] = 0;
	data->fd[1] = 1;

	exe_get_total_redirections_and_pipes(data, data->tree);
	return (SUCCESS);
}
