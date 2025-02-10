#include "./includes/ms.h"

int	ms_error(char *str, char *msg, int err_code, int return_code)
{
	(void) err_code;
	if (ft_strequ(msg, ERR_CMD_NOT_FOUND))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO);
	}
	else if (errno)
	{
//		printf("errno = %d\n", errno);
		if (errno == EISDIR)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd(ERR_IS_DIR, STDERR_FILENO);
		}
		else if (errno == EACCES)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd(ERR_PERMISSION, STDERR_FILENO);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd(ERR_NO_FILE_OR_DIR, STDERR_FILENO);
		}
		else if (errno == ENOTDIR)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd(ERR_NOT_DIR, STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		// set signal to errno
	}
	else if (msg) 
	{
		ft_putstr_fd("(no errno) minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		// set signal to err_code
	//	exit (err_code);
	}
	else
	{
		ft_putendl_fd(str, STDERR_FILENO);
		// set signal to err_code
	}
	return (return_code);
}
