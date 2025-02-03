#include "./includes/ms.h"

void	heredoc_eof(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;
	char	*tmp;
	
	while (1)
	{
		rl = readline("> ");
		if (!rl)
		{
			//free(rl); //have it here before merge signals_2
			heredoc_eof(eof);
			break ;
		}
		if (ft_strequ(rl, eof))
		{
			free(rl); //have it here before merge signals_2
			break ;
		}
		if (expansion == 1)
    		tmp = expand_token_content(rl, data->env, data->exit_code);
		else
    		tmp = ft_strdup(rl);
		ft_putendl_fd(tmp, _out); // Write immediately
		free(rl);
		free(tmp);
	}
//	close(_out);
//	free(eof);
//	return (0); signals_2 has int function, not void
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
/*
int	ms_handle_heredoc(t_data *data, char *delimiter)
{
	pid_t	pid;
	int		_fd[2];
	int		expansion;
	int		status;
	int		heredoc_status;

	expansion = 1;
	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter);
		expansion = 0;
	}
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	pid = fork();
	if (pid == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)
	{
		close(_fd[READ]);
		heredoc_signal();
		ms_exe_heredoc(data, _fd[1], delimiter, expansion);
		close(_fd[WRITE]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(_fd[WRITE]);
	data->fd[0] = _fd[0];
	heredoc_status = (WEXITSTATUS(status) - 1);
	return (heredoc_status);
} */
