#include "./includes/ms.h"

void	ms_exe_set_ast_status(t_tree_node *ast_head)
{
	if (ast_head->type != WORD)
	{
		ast_head->status = READY;
		if (ast_head->type == PIPE)
		{
			if (ast_head->right)
				ast_head->right->status = EXECUTE_CMD;
			if (ast_head->left)
				ast_head->left->status = EXECUTE_CMD;
		}
		if (ast_head->type == REDIN && ast_head->right)
			ast_head->right->status = READ_FROM;
		if (ast_head->type == HEREDOC && ast_head->right)
			ast_head->right->status = READ_HEREDOC;
		if (ast_head->type == REDOUT_T && ast_head->right)
			ast_head->right->status = WRITE_TO_T;
		if (ast_head->type == REDOUT_A && ast_head->right)
			ast_head->right->status = WRITE_TO_A;
	}
	if (ast_head->status == -1)
		ast_head->status = EXECUTE_CMD;
	if (ast_head->left)
		ms_exe_set_ast_status(ast_head->left);
	if (ast_head->right)
		ms_exe_set_ast_status(ast_head->right);
}

int	ms_manage_multiple_infiles(t_data *data, t_tree_node *ast, int file)
{
	(void) ast;
	if (data->redirect_input != 0)
	{
		printf("...closing infile\n");
		close(file); // previous file that was open
	}
	data->redirect_input = 1;
	return (0);
}

int	ms_manage_multiple_outfiles(t_data *data, t_tree_node *ast, int file)
{
	(void) ast;
	if (data->redirect_output != 0)
	{
		printf("...closing outfile\n");
		close(file); // previous file that was open
	}
	data->redirect_output = 1;
	return (0);
}

int	ms_open_file(t_data *data, t_tree_node *ast)
{
	if (ast->status == READ_FROM)
	{
		printf("go open %s with O_RDONLY\n", ast->value[0]);
		ms_manage_multiple_infiles(data, ast, data->fd[0]);
		data->fd[0] = open(ast->value[0], O_RDONLY);
		if (data->fd[0] == -1)
			ft_putendl_fd(ERR_PROCESS_OPEN, STDERR_FILENO);
	}	
	else if (ast->status == READ_HEREDOC)
//		ms_manage_multiple_files();
//		ms_handle_heredoc();
		printf("handle heredoc\n");
	if (ast->status == WRITE_TO_T)
	{
		printf("go open %s with O_CREAT | O_WRONLY | O_TRUNC, 0644\n", ast->value[0]);
		ms_manage_multiple_outfiles(data, ast, data->fd[1]);
		data->fd[1] = open(ast->value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->fd[1] == -1)
			ft_putendl_fd(ERR_PROCESS_OPEN, STDERR_FILENO);
	}
	else if (ast->status == WRITE_TO_A)
	{
		printf("go open %s with O_CREAT | O_WRONLY | O_APPEND, 0644\n", ast->value[0]);
		ms_manage_multiple_outfiles(data, ast, data->fd[1]);
		data->fd[1] = open(ast->value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->fd[1] == -1)
			ft_putendl_fd(ERR_PROCESS_OPEN, STDERR_FILENO);
	}
	return (0);
}

int	ms_handle_pipe_execution(t_data *data, t_tree_node *ast);

int	ms_handle_redirection_execution(t_data *data, t_tree_node *ast)
{
	if (ast->right)
		ms_open_file(data, ast->right);
	if (ast->left && ast->left->status == EXECUTE_CMD)
		printf("go execute the command %s\n", ast->left->value[0]); //ms_exe_command();
	if (ast->left && ast->left->type == PIPE)
		ms_handle_pipe_execution(data, ast->left);
	if (ast->left && (ast->left->type == REDIN || ast->left->type == HEREDOC || ast->left->type == REDOUT_T || ast->left->type == REDOUT_A))
		ms_handle_redirection_execution(data, ast->left);
	return (0);
}

int	ms_handle_pipe_execution(t_data *data, t_tree_node *ast)
{
	if (ast->status == EXECUTE_CMD)
		printf("go execute the command %s\n", ast->value[0]); //ms_exe_command();
	if (ast->type == REDIN || ast->type == HEREDOC || ast->type == REDOUT_T || ast->type == REDOUT_A)
		return (ms_handle_redirection_execution(data, ast));
	if (ast->left)
		ms_handle_pipe_execution(data, ast->left);
	if (ast->right)
		ms_handle_pipe_execution(data, ast->right);
	return (0);
}

int	ms_exe_command(t_data *data, char **_cmd)
{
		if (builtins(_cmd[0]))
			return (ms_exe_builtin(data, _cmd));
		else
			return (ms_exe_external_cmd(data, _cmd));
	return (0);
}

int	ms_exe_ast(t_data *data, t_tree_node *ast)
{
	int	pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (ast->status == EXECUTE_CMD)
	{
		ms_exe_command(data, ast->value);
	}
	if (ast->status == READY)
	{
		if (ast->type == PIPE)
			ms_handle_pipe_execution(data, ast);
		if (ast->type == REDIN || ast->type == HEREDOC || ast->type == REDOUT_T || ast->type == REDOUT_A)
			ms_handle_redirection_execution(data, ast);
	}
	return (0);
}

int	ms_exe_pipeline(t_data *data)
{
	ms_exe_set_ast_status(data->tree);
	ms_exe_ast(data, data->tree);
	return (0);
}
