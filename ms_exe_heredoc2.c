#include "./includes/ms.h"

void	free_string_array(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(arr[i++]);
	free(arr);
}

/*void	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;
	char	*tmp;
	//int		interrupted;
	//char	**lines;
	//int		i;
	//int		j;

	//interrupted = 0;
	//lines = malloc(sizeof(char *) * 1024); 
	//i = 0;
	while (1)
	{
		rl_done = 0;
		printf("Debug before readline: rl_done = %d\n", rl_done);
        rl = readline("> ");
        printf("Debug after readline: rl_done = %d\n", rl_done);
		if (!rl)
		{
			//free_string_array(lines, i);
			close(_out);
			free(eof);
			exit(0);
		}
		//if (rl_done)
		//{
			//free(rl);
			//break ;
		//}
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
		//lines[i++] = tmp;
		ft_putendl_fd(tmp, _out);
	}
	//only write if we haven't been interrupted
	//j = 0;
	//while (j < i)
	//{
		//ft_putendl_fd(lines[j], _out);
		//free(lines[j]);
		//j++;
	//}
	//free(lines);
	close(_out);
	free(eof);
}*/

void	heredoc_eof(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion)
{
	char	*rl;
	char	*tmp;
	
	while (1)
	{
		rl = readline("> ");
		if (!rl || ft_strequ(rl, eof) )
		{
			heredoc_eof(eof);
			break ;
		}
		if (expansion == 1)
    		tmp = expand_token_content(rl, data->env, data->exit_code);
		else
    		tmp = ft_strdup(rl);
		ft_putendl_fd(tmp, _out); // Write immediately
		free(tmp);
	}
	close(_out);
	free(eof);
	return (0);
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
		close(_fd[READ]);
		heredoc_signal();
		status = ms_exe_heredoc(data, _fd[1], delimiter, expansion);
		close(_fd[WRITE]);
		exit(data->exit_code);
	}
	waitpid(pid, &status, 0); // changed this one
	close(_fd[WRITE]); // close write end _fd[1]
	printf("WIFEXITED(status): %d\n", WIFEXITED(status));
	printf("WIFSIGNALED(status): %d\n", WIFSIGNALED(status));
	printf("WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
	printf("WTERMSIG(status): %d\n", WTERMSIG(status));
	if (WIFEXITED(status))  // Check if child exited normally
    	data->exit_code = WEXITSTATUS(status);  // Extract the actual exit code
	else if (WIFSIGNALED(status))  // Check if child was terminated by a signal
	{
    	data->exit_code = 128 + WTERMSIG(status);  // Set exit code for signals
    	rl_on_new_line();
		printf("data->fd[0] before: %d\n", data->fd[0]);
    	write(1, "\n", 1);
		close(_fd[READ]);  // Close read end if interrupted
        data->fd[0] = -1;  // Signal to parent that heredoc was interrupted
		printf("data->fd[0] after: %d\n", data->fd[0]);
        return (1);
	}
	data->fd[0] = _fd[0];
	printf("Heredoc interrupted, exit_code: %d, data->fd[0]: %d\n", data->exit_code, data->fd[0]);
	return (0);
} 
