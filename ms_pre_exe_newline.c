#include "./includes/ms.h"

void	exe_get_total_redirections_and_pipes(t_data *data, t_tree_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
		data->count_pipe += 1;
	else if (ast->type == REDIN || ast->type == HEREDOC)
	{
		data->count_infile += 1;
		if (ast->type == HEREDOC)
			data->count_heredoc += 1;
	}
	else if (ast->type == REDOUT_A || ast->type == REDOUT_T)
		data->count_outfile += 1;
	if (ast->left)
		exe_get_total_redirections_and_pipes(data, ast->left);
	if (ast->right)
		exe_get_total_redirections_and_pipes(data, ast->right);
	if (data->count_pipe)
		data->processes = data->count_pipe + 1;
}

int	ms_pre_exe_newline(t_data *data)
{
	data->envp = env_get_array_str(data);
	if (!data->envp)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	data->envp_path = exe_get_path(data->envp);
	if (!data->envp_path)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	data->count_infile = 0;
	data->count_outfile = 0;
	data->count_pipe = 0;
	data->count_heredoc = 0;
	data->redirect_input = 0;
	data->redirect_output = 0;
	data->heredoc = 0;
	data->processes = 0;
	data->count_child = 0;
	data->fd[0] = STDIN_FILENO;
	data->fd[1] = STDOUT_FILENO;
	exe_get_total_redirections_and_pipes(data, data->tree);
	data->pid = malloc(sizeof(int) * (data->count_pipe + 1));
	if (!data->pid)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	if (data->count_heredoc > 16)//exit bash with code 2
		return (ft_putendl_fd("minishell: maximum here-document count exceeded", STDERR_FILENO), FAILURE);
	return (SUCCESS);
}

//void	ms_exe_set_heredoc(t_data *data, t_tree_node *ast)
int	ms_exe_set_heredoc(t_data *data, t_tree_node *ast)
{
	int	status_left;
	int	status_right;

	if(!ast)
		return (SUCCESS);
	if (ast->type == HEREDOC)
	{
		printf("before open heredoc %s: fd[read] = %d\n", ast->right->value[0], ast->right->fd[READ]);
		ms_heredoc(data, ast, ast->right->value[0]);
	//	printf("delimiter: %s after open heredoc: fd[read] = %d\n", ast->value[0], ast->fd[READ]);
	}
//	if (ast->left)
	status_left = ms_exe_set_heredoc(data, ast->left);
//	if (ast->right)
	status_right = ms_exe_set_heredoc(data, ast->right);
	if (status_left != SUCCESS || status_right != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
