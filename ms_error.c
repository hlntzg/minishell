#include "./includes/ms.h"

int	ms_error(char *str, char *msg, int err_code, int return_code)
{
	if (errno)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		// set signal to errno
	}
	else if (msg)	// str: command not found (msg = ERR_CMD_NOT_FOUND) 
	{
		fd_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		// set signal to err_code
		exit (err_code);
	}
	else
	{
		ft_putendl_fd(str, STDERR_FILENO);
		// set signal to err_code
	}
	return (return_code);
}
