/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:19:20 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/13 10:20:42 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

void	ms_errno_message(char *str, int errno_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno_code == EISDIR)
		ft_putendl_fd(ERR_IS_DIR, STDERR_FILENO);
	else if (errno_code == EACCES)
		ft_putendl_fd(ERR_PERMISSION, STDERR_FILENO);
	else if (errno_code == ENOENT)
		ft_putendl_fd(ERR_NO_FILE_OR_DIR, STDERR_FILENO);
	else if (errno_code == ENOTDIR)
		ft_putendl_fd(ERR_NOT_DIR, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno_code), STDERR_FILENO);
}

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
		ms_errno_message(str, errno);
	}
	else if (msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else
		ft_putendl_fd(str, STDERR_FILENO);
	return (return_code);
}
