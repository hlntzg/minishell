/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:05 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/09 17:07:46 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	heredoc_eof(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

/* maybe the lines can be reduced by eliminating the tmp var*/
void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;
	int		flag;
	char	*tmp;

	while (1)
	{
		heredoc_signal();
		rl = readline("> ");
		if (!rl)
		{
			if (g_sig != SIGINT)
				heredoc_eof(eof);
			if (g_sig == SIGINT)
			{
//				std_reset(data);
				close_heredoc_fds(data->tree);
			}
			break ;
		}
		//if (!rl && g_sig == SIGINT)
		//{
		//	printf("from end herdoc\n");
			//exit(130);
			//if (rl)
			//	free(rl);
			//close(0);
			//ms_free_and_exit_child(data, 130);
		//	break ;
		//}

		if (ft_strequ(rl, eof))
		{
			free(rl);
			break ;
		}
		if (expansion)
			tmp = expand_token_content(rl, data, &flag);
//			rl = expand_token_content(rl, data->env, data->exit_code, &flag);
		else
			tmp = ft_strdup(rl);
		//ft_putendl_fd(tmp, _out);
		ft_putendl_fd(tmp, _out);
		free(rl);
		free(tmp);
	}

}

int	quoted_eof(char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == 34 || *delimiter == 39)
			return (1);
		delimiter++;
	}
	return (0);
}

/*
 * "EOF" or 'EOF' 	= EOF
 * '"'EOF'"'		= "EOF"
 * "'EOF'"			= 'EOF'
 * '"EOF"'			= "EOF"
 * '""'EOF'""'		= ""EOF""
 * '''EOF'''		= EOF
 * """"EOF""""		= EOF
 */
char	*update_eof(char *delimiter)
{
	char	*new_eof;
	int		i;
	int		s_quote;
	int		d_quote;

	new_eof = ft_strdup("");
	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (delimiter[i])
	{
		new_eof = process_character(new_eof, delimiter[i], &s_quote, &d_quote);
		i++;
	}
	return (new_eof);
}

int	ms_heredoc(t_data *data, t_tree_node *ast, char *delimiter)
{
	//pid_t	pid;
	int		status;
	int		expansion;
	char	*tmp;

	status = 0;
	expansion = 1;
	tmp = NULL;

	std_save(data);
	if (quoted_eof(delimiter))
	{
		tmp = update_eof(delimiter);
		expansion = 0;
	}
	if (pipe(ast->fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	if (tmp)
		ms_exe_heredoc(data, ast->fd[1], tmp, expansion);
	else
		ms_exe_heredoc(data, ast->fd[1], delimiter, expansion);
	free(tmp);
//	if (g_sig == SIGINT)
//	{
//		close_heredoc_fds(data->tree);
//		std_reset(data);
//		close(ast->fd[READ]);
//	}
	if (g_sig != SIGINT)
		close(ast->fd[WRITE]);
	std_reset(data);
	restore_main_signals();
//	free(tmp);
	return (status);
}
/*
int	ms_heredoc(t_data *data, t_tree_node *ast, char *delimiter)
{
	pid_t	pid;
	int		status;
	int		expansion;
	char	*tmp;

	status = 0;
	expansion = 1;
	tmp = NULL;
	signal(SIGINT, heredoc_sigint_exe);
	if (quoted_eof(delimiter))
	{
		tmp = update_eof(delimiter);
		expansion = 0;
	}
	if (pipe(ast->fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	pid = fork();
	if (pid == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)
	{
		heredoc_signal();
		close(ast->fd[READ]);
		if (tmp)
			ms_exe_heredoc(data, ast->fd[1], tmp, expansion);
		else
			ms_exe_heredoc(data, ast->fd[1], delimiter, expansion);
		close(ast->fd[WRITE]);
		free(tmp);
		ms_free_and_exit_child(data, status);
	}
	waitpid(pid, &status, 0);
	if (g_sig == SIGINT)
	{
//		close_heredoc_fds(data->tree);
		close(ast->fd[READ]);
	}
	close(ast->fd[WRITE]);
	restore_main_signals();
	free(tmp);
	return (status);
}*/
