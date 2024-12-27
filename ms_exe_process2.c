int	process_dup(int fd_input, int fd_output)
{
	if (dup2(fd_input, STDIN_FILENO) == -1)
		return (ft_putendl_fd(ERR_PROCESS_DUP2, STDERR_FILENO), FAILURE);
	if (dup2(fd_output, STDOUT_FILENO) == -1)
		return (ft_putendl_fd(ERR_PROCESS_DUP2, STDERR_FILENO), FAILURE);
	return (SUCCESS);
}

int	first_process_dup_infile(t_data *data, t_cmd *cmd)
{
	if (data->total_cmds == 1)
		return (process_dup(cmd->infile, STDOUT_FILENO));
	else
		return (process_dup(cmd->infile, data->fd[1]));
}

int	first_process_dup_heredoc(t_data *data, t_cmd *cmd)
{
	int	status;

	if (data->total_cmds == 1)
	{
		status = process_dup(cmd->tmp_doc[0], STDOUT_FILENO);
		if (close(cmd->tmp_doc[0]) == -1)
			return (ft_putendl_fd(ERR_PROCESS_CLOSE, STDERR_FILENO), FAILURE);
		return (status);
	}
	else
		return (process_dup(cmd->tmp_doc[0], data->fd[1]));
}

int	first_process(t_data *data, t_cmd *cmd)
{
	int	status;

	if (cmd->infile != -1)
		status = first_process_dup_infile(cmd);
	else if (cmd->heredoc != -1)
		status = first_process_dup_heredoc(cmd);
	if (cmd->outfile_a != -1)
		status = process_dup(STDIN_FILENO, cmd->outfile_a);
	else if (cmd->outfile_t != -1)
		status = process_dup(STDIN_FILENO, cmd->outfile_t);
	//if (data->total_cmds != 1)
	//	status = process_dup(STDIN_FILENO, data->fd[1]);
	return (status);
}
/*
int	middle_process(t_data *data, t_cmd *cmd)
{
}

int	last_process(t_data *data, t_cmd *cmd)
{
}
*/
