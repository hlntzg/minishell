int	ms_handle_heredoc(t_data *data, char *delimiter)
{
	pid_t	pid;
	int		_fd[2];
	int		expansion;
	int		status;
	struct sigaction sa_ignore, sa_restore;

	expansion = 1;

	// Handle quoted EOF
	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter); // Update delimiter to remove quotes
		expansion = 0;
	}

	// Create pipe
	if (pipe(_fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));

	// Fork the process
	if ((pid = fork()) == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0) // Child process
	{
		close(_fd[READ]); // Close read end in child
		heredoc_signal(); // Set child-specific signal handling
		if (ms_exe_heredoc(data, _fd[1], delimiter, expansion) == 1)
			return (1); // If interrupted, exit early
		close(_fd[WRITE]);
		exit(data->exit_code);
	}

	// Parent process
	close(_fd[WRITE]); // Close write end in parent

	// Ignore SIGINT temporarily
	sa_ignore.sa_handler = SIG_IGN; // Ignore SIGINT
	sigaction(SIGINT, &sa_ignore, &sa_restore);

	// Wait for child process
	waitpid(pid, &status, 0);

	// Restore original SIGINT handler
	sigaction(SIGINT, &sa_restore, NULL);

	// Handle child exit status
	if (WIFEXITED(status))  // Check if child exited normally
		data->exit_code = WEXITSTATUS(status);  // Extract the actual exit code
	else if (WIFSIGNALED(status))  // Check if child was terminated by a signal
	{
		data->exit_code = 128 + WTERMSIG(status);  // Set exit code for signals
		rl_on_new_line();
		write(1, "\n", 1);
		close(_fd[READ]);  // Close read end if interrupted
		data->fd[0] = -1;  // Signal to parent that heredoc was interrupted
		return (data->exit_code);
	}

	// Pass read end of pipe to `data->fd[0]`
	data->fd[0] = _fd[READ];
	return (data->exit_code);
}


void	heredoc_signal(void)
{
	struct sigaction sa;

	// Set SIGINT to default behavior
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	// Ignore SIGQUIT
	signal(SIGQUIT, SIG_IGN);
}

