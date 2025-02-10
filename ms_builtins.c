/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:45:35 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/10 16:40:44 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	builtins(char *cmd)
{
	return (ft_strequ(cmd, "echo") || ft_strequ(cmd, "cd")
		|| ft_strequ(cmd, "pwd") || ft_strequ(cmd, "export")
		|| ft_strequ(cmd, "unset") || ft_strequ(cmd, "env")
		|| ft_strequ(cmd, "exit"));
}

/*
 * echo		- accepts redir out
 * env		- accepts redir out
 * export	- accepts redir out if there isnt any argument
 * pwd		- accepts redir out
 */
int	ms_builtin_execution(t_data *data, char **_cmd, int *_out)
{
	int	status;

	status = 0;
	if (data->redirect_input && !data->processes)
	{
		if (data->fd[0] == -1)
			return (1);
		else
			close(data->fd[0]);
	}
	if (ft_strequ(_cmd[0], "cd"))
		status = ms_cd(data, _cmd);
	else if (ft_strequ(_cmd[0], "echo"))
		status = ms_echo(data, _cmd, _out);
	else if (ft_strequ(_cmd[0], "env"))
		status = ms_env(data, _cmd, _out);
	else if (ft_strequ(_cmd[0], "exit"))
		status = ms_exit(data, _cmd);
	else if (ft_strequ(_cmd[0], "export"))
		status = ms_export(data, _cmd, _out);
	else if (ft_strequ(_cmd[0], "pwd"))
		status = ms_pwd(data, _cmd, _out);
	else if (ft_strequ(_cmd[0], "unset"))
		status = ms_unset(data, _cmd);
	return (status);
}

int	count_cmd_args(char **_cmd)
{
	int	i;

	i = 0;
	while (_cmd[i])
		i++;
	return (i);
}

bool	valid_builtin_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (false);
	return (true);
}
