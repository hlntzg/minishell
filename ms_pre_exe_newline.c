/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pre_exe_newline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:32:44 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 13:33:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	exe_get_total_redirections_and_pipes(t_data *data, t_tree_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
		data->count_pipe += 1;
	else if (ast->type == REDIN || ast->type == HEREDOC)
		data->count_infile += 1;
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
	data->std[0] = STDIN_FILENO;
	data->std[1] = STDOUT_FILENO;
	exe_get_total_redirections_and_pipes(data, data->tree);
	data->pid = malloc(sizeof(int) * (data->count_pipe + 1));
	if (!data->pid)
		return (ms_error(ERR_MALLOC_FAIL, NULL, 1, FAILURE));
	return (SUCCESS);
}

void	ms_exe_set_heredoc(t_data *data, t_tree_node *ast)
{
	if (ast->status == READ_HEREDOC && g_sig != SIGINT)
		ms_heredoc(data, ast, ast->value[0]);
	if (ast->type == PIPE)
	{
		if (ast->left)
			ms_exe_set_heredoc(data, ast->left);
		if (ast->right)
			ms_exe_set_heredoc(data, ast->right);
	}
	else
	{
		if (ast->right)
			ms_exe_set_heredoc(data, ast->right);
		if (ast->left)
		{
			if (ast->left->status != EXECUTE_CMD
				&& ast->right->status == READ_HEREDOC)
			{
				if (g_sig != SIGINT)
					close(ast->right->fd[READ]);
			}
			ms_exe_set_heredoc(data, ast->left);
		}
	}
}
