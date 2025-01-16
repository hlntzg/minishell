#include "./includes/ms.h"

void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	(void) data;
	char	*rl;

	while (1)
	{
		rl = readline("> ");
		if (!rl || ft_strequ(rl, eof))
		{
			free(rl);
			break ;
		}
		if (expansion)
		{
			printf("handle expansion inside heredoc\n");
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
		if (*delimiter == '"' || *delimiter == '\'')
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
	//some natalie's code for handle quotes
	return (delimiter);
}

int	ms_handle_heredoc(t_data *data, char *delimiter)
{
	//printf("delimiter = %s", delimiter);
	pid_t	pid;
	int		_fd[2];
	int		expansion;
	int		status;

	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter); //update delimiter to remove quotes
		expansion = 1;
	}
	else
		expansion = 0;
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	if ((pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)//child_process
	{
		close(_fd[READ]); // close read end _fd[0]
		ms_exe_heredoc(data, _fd[1], delimiter, expansion);
		exit(0);
	}
	waitpid(pid, &status, 0);
	close(_fd[WRITE]); // close write end _fd[1]
//	data->fd[0] = _fd[0];
	dup2(_fd[0], data->fd[0]);
	return (0);
}
