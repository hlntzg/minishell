#include "./includes/ms.h"

int	ms_heredoc(t_data *data, t_tree_node *ast, char *delimiter)
{
	pid_t	pid;
	int		status;
	int		expansion;

	expansion = 1;
	if (quoted_eof(delimiter))
	{
		delimiter = update_eof(delimiter);
		expansion = 0;
	}
	if (pipe(ast->fd) == -1)
		return (ms_error(ERR_PROCESS_PIPE, NULL, 1, FAILURE));
	pid = fork();
	if (pid == -1)
		return (ms_error(ERR_PROCESS_FORK, NULL, 1, FAILURE));
	else if (pid == 0)
	{
		close(ast->fd[READ]);
		ms_exe_heredoc(data, ast->fd[1], delimiter, expansion);
		close(ast->fd[WRITE]);
		exit(1);
	}
	waitpid(pid, &status, 0);
	close(ast->fd[WRITE]);
	//data->fd[0] = ast->fd[READ];
	//close(ast->fd[READ]);
	return (status);
}
