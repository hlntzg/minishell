#include "./includes/ms.h"

int	ms_manage_multiple_infiles(t_data *data, t_tree_node *ast, int file)
{
	if (data->fd[0] == -1)
		return (-1);
	else// (data->fd[0] != -1)
	{
		if (data->redirect_input != 0)
			close(file);
		data->redirect_input = 1;
	}
	if (access(ast->value[0], F_OK) == -1 || access(ast->value[0], R_OK) == -1)
	{
		data->fd[0] = -1;
		return (ms_error(ast->value[0], NULL, -1, -1));
	}
	return (0);
}

int	ms_manage_multiple_outfiles(t_data *data, t_tree_node *ast, int file)
{
	if (data->fd[1] == -1)
		return (-1);
	else
	{
		if (data->redirect_output != 0)
			close(file);
		data->redirect_output = 1;
	}
	if (access(ast->value[0], F_OK) == 0 && access(ast->value[0], W_OK) == -1)
	{
		data->fd[1] = -1;
		return (ms_error(ast->value[0], NULL, -1, -1));
	}
	return (0);
}

int	ms_open_file(t_data *data, t_tree_node *ast)
{
	int	open_mode;

	if (ast->status == READ_FROM)
	{
		if (ms_manage_multiple_infiles(data, ast, data->fd[0]) == -1)
			return (-1);
		data->fd[0] = open(ast->value[0], O_RDONLY);
		if (data->fd[0] == -1)
			ft_putendl_fd(ERR_PROCESS_OPEN, STDERR_FILENO);
	}	
	else if (ast->status == READ_HEREDOC)
	{
		ms_manage_multiple_infiles(data, ast, data->fd[0]);
		ms_handle_heredoc(data, ast->value[0]);
	}
	if (ast->status == WRITE_TO_T || ast->status == WRITE_TO_A)
	{
		if (ms_manage_multiple_outfiles(data, ast, data->fd[1]) == -1)
			return (-1);
		open_mode = O_TRUNC;
		if (ast->status == WRITE_TO_A)
			open_mode = O_APPEND;
		data->fd[1] = open(ast->value[0], O_CREAT | O_WRONLY | open_mode, 0666);
		if (data->fd[1] == -1)
			ft_putendl_fd(ERR_PROCESS_OPEN, STDERR_FILENO);
	}
	return (0);
}

int	ms_handle_redirection_execution(t_data *data, t_tree_node *ast, int *_pipe_fd)
{
	int	status;

	if (ast->right)
		status = ms_open_file(data, ast->right);
	if (ast->left && ast->left->status == EXECUTE_CMD)
		status = ms_exe_command(data, ast->left->value, _pipe_fd);
	if (ast->left && ast->left->type == PIPE)
		status = ms_handle_pipe_execution(data, ast->left, _pipe_fd);
	if (ast->left && (ast->left->type == REDIN || ast->left->type == HEREDOC
			|| ast->left->type == REDOUT_T || ast->left->type == REDOUT_A))
		status = ms_handle_redirection_execution(data, ast->left, _pipe_fd);
	return (status);
}

int	ms_handle_pipe_execution(t_data *data, t_tree_node *ast, int *_pipe_fd)
{
	int	status;

	if (ast->status == EXECUTE_CMD)
		status = ms_exe_command(data, ast->value, _pipe_fd);
	if (ast->type == REDIN || ast->type == HEREDOC
		|| ast->type == REDOUT_T || ast->type == REDOUT_A)
		return (ms_handle_redirection_execution(data, ast, _pipe_fd));
	if (ast->left)
		status = ms_handle_pipe_execution(data, ast->left, _pipe_fd);
	if (ast->right)
		status = ms_handle_pipe_execution(data, ast->right, _pipe_fd);
	return (status);
}
