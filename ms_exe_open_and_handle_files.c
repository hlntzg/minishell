/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_open_and_handle_files.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:21 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/14 10:26:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	ms_manage_multiple_outfiles(t_data *data, t_tree_node *ast, int file)
{
	if (data->fd[1] == -1 || data->fd[0] == -1)
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

int	ms_manage_multiple_infiles(t_data *data, t_tree_node *ast, int file)
{
	(void)file;
	if (ast->status == READ_HEREDOC)
		data->heredoc = 1;
	else
		data->heredoc = 0;
	if (data->fd[0] == -1 && data->redirect_input)
		return (-1);
	data->redirect_input = 1;
	if (!data->heredoc && (access(ast->value[0], F_OK | R_OK) == -1))
	{
		data->fd[0] = -1;
		return (ms_error(ast->value[0], NULL, -1, -1));
	}
	return (0);
}

int	ms_open_infile(t_data *data, t_tree_node *ast, t_tree_node *prev)
{
	if (ast->status == READ_FROM)
	{
		if (ms_manage_multiple_infiles(data, ast, data->fd[0]) == -1)
			return (-1);
		data->fd[0] = open(ast->value[0], O_RDONLY);
		if (data->fd[0] == -1)
			return (ms_error(ast->value[0], NULL, 1, 1));
		if (!prev->left)
			close(data->fd[0]);
		else if (prev->left->type == REDIN || prev->left->type == HEREDOC)
			close(data->fd[0]);
	}	
	else if (ast->status == READ_HEREDOC)
	{
		if (ms_manage_multiple_infiles(data, ast, data->fd[0]) == -1)
		{
			close(ast->fd[READ]);
			return (-1);
		}
		if (!prev->left)
			close(ast->fd[READ]);
		else
			data->fd[0] = ast->fd[READ];
	}
	return (0);
}

int	ms_open_outfile(t_data *data, t_tree_node *ast, t_tree_node *prev)
{
	int	open_mode;

	(void) prev;
	if (ast->status == WRITE_TO_T || ast->status == WRITE_TO_A)
	{
		if (ms_manage_multiple_outfiles(data, ast, data->fd[1]) == -1)
			return (-1);
		open_mode = O_TRUNC;
		if (ast->status == WRITE_TO_A)
			open_mode = O_APPEND;
		data->fd[1] = open(ast->value[0], O_CREAT | O_WRONLY | open_mode, 0666);
		if (data->fd[1] == -1)
			return (ms_error(ast->value[0], NULL, 1, 1));
	}
	return (0);
}

int	ms_open_file(t_data *data, t_tree_node *ast, t_tree_node *prev)
{
	char	*tmp;

	tmp = NULL;
	if ((ast->status == READ_FROM || ast->status == WRITE_TO_T
			|| ast->status == WRITE_TO_A) && ast->expand == 1)
	{
		tmp = ft_strtrim(ast->value[0], " \t\n\v\f\r");
		if (ft_strchr(tmp, 32))
		{
			free(tmp);
			return (ms_error(ERR_AMBIGUOUS_REDIR, NULL, FAILURE, FAILURE));
		}
		free(tmp);
	}
	if (ast->status == READ_FROM || ast->status == READ_HEREDOC)
		return (ms_open_infile(data, ast, prev));
	if (ast->status == WRITE_TO_T || ast->status == WRITE_TO_A)
		return (ms_open_outfile(data, ast, prev));
	return (0);
}
