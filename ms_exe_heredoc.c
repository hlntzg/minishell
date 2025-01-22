#include "./includes/ms.h"

void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;

	while (1)
	{
		rl = readline("> ");
		if (!rl || ft_strequ(rl, eof))
		{
			free(rl);
			break ;
		}
		if (expansion == 1)
		{
			rl = expand_token_content(rl, data->env, data->exit_code);
		}
		ft_putendl_fd(rl, _out);
		if (rl)
			free(rl);
	}
	free(eof);
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

int	ms_handle_heredoc(t_data *data, char *delimiter)
{
	pid_t	pid;
	int		_fd[2];
	int		expansion;
	int		status;

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
		ms_exe_heredoc(data, _fd[1], delimiter, expansion);
		close(_fd[WRITE]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(_fd[WRITE]);
	data->fd[0] = _fd[0];
	return (0);
}
