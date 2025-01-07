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

void	ms_handle_pipe_execution(t_tree_node *ast)
{
	if (ast->status == EXECUTE_CMD)
		printf("go execute the command %s\n", ast->value[0]);
	if (ast->left)
		ms_handle_pipe_execution(ast->left);
	if (ast->right)
		ms_handle_pipe_execution(ast->right);
}

int	ms_exe_ast(t_data *data, t_tree_node *ast)
{
	if (ast->status == EXECUTE_CMD)
	{
		if (builtins(ast->value[0]))
			return (ms_exe_builtin(data, ast->value));
		else
			return (ms_exe_external_cmd(data, ast->value));
	}
	if (ast->status == READY)
	{
		if (ast->type == PIPE)
			ms_handle_pipe_execution(ast);
		if (ast->type == REDIN)
			printf("execute redin\n");
	}
	return (0);
}

int	ms_exe_pipeline(t_data *data)
{
	ms_exe_set_ast_status(data->tree);
	ms_exe_ast(data, data->tree);
	return (0);
}
