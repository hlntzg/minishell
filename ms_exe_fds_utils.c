/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_fds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:14:27 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 13:18:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	std_save(t_data *data)
{
	data->std[0] = dup(STDIN_FILENO);
	data->std[1] = dup(STDOUT_FILENO);
	if (data->std[0] == -1 || data->std[1] == -1)
		return (0);
	return (1);
}

int	std_reset(t_data *data)
{
	if (dup2(data->std[0], 0) < 0 || dup2(data->std[1], 1) < 0)
		return (0);
	close(data->std[0]);
	close(data->std[1]);
	data->std[0] = -1;
	data->std[1] = -1;
	return (1);
}

void	close_fds(int read, int write)
{
	close(read);
	close(write);
}

void	close_heredoc_fds(t_tree_node *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	if (ast->status == READ_HEREDOC)
	{
		while (i < 2)
		{
			if (ast->fd[i] != -1)
				close(ast->fd[i]);
			i++;
		}
	}
	if (ast->left)
		close_heredoc_fds(ast->left);
	if (ast->right)
		close_heredoc_fds(ast->right);
}

void	close_free_and_exit_child(t_data *data, int *_pipe_fd, int *_fd)
{
	close_fds(_fd[READ], _fd[WRITE]);
	if (_pipe_fd[0] != -1)
		close(_pipe_fd[0]);
	close_heredoc_fds(data->tree);
	ms_free_and_exit_child(data, 1);
}
