#include "./includes/ms.h"

void	free_string_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
}

void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;
	char	*tmp;
	int		interrupted;

	interrupted = 0;
	rl_done = 0;
	while (1)
	{
		printf("Debug before readline: rl_done = %d\n", rl_done);
        rl = readline("> ");
        printf("Debug after readline: rl_done = %d\n", rl_done);
		if (!rl)
		{
			close(_out);
			free(eof);
			exit(0);
		}
		if (rl_done == 1)
		{
			interrupted = 1;
			free(rl);
			break ;
		}
		if (ft_strequ(rl, eof))
		{
			free(rl);
			break;
		}
		if (expansion == 1)
			tmp = expand_token_content(rl, data->env, data->exit_code);
		else
			tmp = ft_strdup(rl);
		free(rl);
		// lines[i++] = tmp;
		ft_putendl_fd(tmp, _out);
	}
	//only write if we haven't been interrupted
	//while (j < i)
	//{
		//ft_putendl_fd(lines[j], _out);
		//free(lines[j]);
		//j++;
	//}
	//free(lines);
	close(_out);
	free(eof);
}

/*void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;

	while (1)
	{
		rl = readline("> ");
		if (!rl || ft_strequ(rl, eof) )
		{
			close(_out);
			free(rl);
			exit(0);
		}
		if (ft_strequ(rl, eof))
		{
			free(rl);
			break ;
		}
		if (expansion == 1)
			rl = expand_token_content(rl, data->env, data->exit_code);
		ft_putendl_fd(rl, _out);
		if (rl)
			free(rl);
	}
	close(_out);
	free(eof);
}*/

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
	int	s_quote;
	int	d_quote;
	int	i;
	char	*new_eof;

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

	//heredoc_signal();
	expansion = 1;
	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter); //update delimiter to remove quotes
		expansion = 0;
	}
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	if ((pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)//child_process
	{
		close(_fd[READ]); //new close read end child
		child_signal();
		ms_exe_heredoc(data, _fd[1], delimiter, expansion);
		exit(data->exit_code);
	}
	close(_fd[WRITE]); //new close write end child 
	waitpid(pid, &status, 0); // changed this one
	if (status == 2)  // Check if child was terminated by a signal
	{
		data->exit_code = 130;  // Set exit code to 128 + signal number
		rl_on_new_line();
		write(1, "\n", 1);
	}
	else
		data->exit_code = status;
	dup2(_fd[0], data->fd[0]);
	close(_fd[WRITE]); // close write end _fd[1]
	return (data->exit_code);
} 
