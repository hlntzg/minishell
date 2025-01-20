/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_heredoc3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:05:51 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/20 16:05:54 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	handle_child_heredoc(t_data *data, int _fd[2], char *eof, int expansion)
{
	close(_fd[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ms_exe_heredoc(data, _fd[1], eof, expansion);
	exit(data->exit_code);
}

int	setup_heredoc(t_data *data, char *delimiter, int _fd[2], pid_t *pid)
{
	int	expansion;

	expansion = 1;
	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter);
		expansion = 0;
	}
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	if ((*pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	if (*pid == 0)
		handle_child_heredoc(data, _fd, delimiter, expansion);
	return (SUCCESS);
}

int	ms_handle_heredoc(t_data *data, char *delimiter)
{
	pid_t	pid;
	int		_fd[2];
	int		status;

	heredoc_signal();
	if (setup_heredoc(data, delimiter, _fd, &pid) == FAILURE)
		return (FAILURE);
	close(_fd[1]);
	waitpid(pid, &status, 0);
	if (status == 2)
	{
		data->exit_code = 130;
		write(1, "\n", 1);
	}
	else
		data->exit_code = status;
	dup2(_fd[0], data->fd[0]);
	close(_fd[0]);
	return (data->exit_code);
}

int	process_heredoc_line(t_data *data, char *eof, t_lines *lines, int expansion)
{
	char	*rl;
	char	*tmp;

	rl = readline("> ");
	if (!rl)
	{
		cleanup_heredoc(lines, -1, eof);
		exit(0);
	}
	if (ft_strequ(rl, eof))
	{
		free(rl);
		return (1);
	}
	if (expansion == 1)
		tmp = expand_token_content(rl, data->env, data->exit_code);
	else
		tmp = ft_strdup(rl);
	free(rl);
	lines->arr[lines->count++] = tmp;
	return (0);
}

void	write_heredoc_lines(int fd, t_lines *lines)
{
	int	i;

	i = 0;
	while (i < lines->count)
	{
		ft_putendl_fd(lines->arr[i], fd);
		i++;
	}
}

void	cleanup_heredoc(t_lines *lines, int fd, char *eof)
{
	int	i;

	i = 0;
	while (i < lines->count)
		free(lines->arr[i++]);
	free(lines->arr);
	if (fd != -1)
		close(fd);
	free(eof);
}

void	init_lines(t_lines *lines)
{
	lines->arr = malloc(sizeof(char *) * 1024);
	lines->count = 0;
}

void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	t_lines	lines;

	init_lines(&lines);
	while (1)
	{
		if (process_heredoc_line(data, eof, &lines, expansion) == 1)
			break;
	}
	write_heredoc_lines(_out, &lines);
	cleanup_heredoc(&lines, _out, eof);
}
