/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:14:15 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/13 14:45:05 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

char	*ms_set_dir(t_data *data, char *dir)
{
	(void)data;
	if (getcwd(NULL, 0) == NULL)
		return (NULL);
	else
		return (ft_strdup(dir));
}

void	ms_update_oldpwd(t_data *data, char *old_cwd)
{
	if (env_get_node(data, "OLDPWD"))
		env_update_value(data, "OLDPWD", old_cwd);
}

void	ms_update_pwd(t_data *data, char *new_cwd)
{
	if (env_get_node(data, "PWD"))
		env_update_value(data, "PWD", new_cwd);
	else if (env_get_node(data, "OLDPWD"))
		env_update_value(data, "OLDPWD", ft_strdup(""));
}

static int	ms_handle_cd(t_data *data, char *dir)
{
	char	*old_pwd;

	if (!dir)
	{
		dir = env_get_value(data, "HOME");
		if (!dir || !dir[0])
			return (free(dir), ms_error(ERR_CD_NOHOME, NULL, FAILURE, FAILURE));
	}
	old_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		ms_error(dir, NULL, FAILURE, FAILURE);
		free(dir);
		free(old_pwd);
		return (FAILURE);
	}
	if (old_pwd)
		ms_update_oldpwd(data, ft_strdup(old_pwd));
	ms_update_pwd(data, getcwd(NULL, 0));
	free(old_pwd);
	free(dir);
	return (SUCCESS);
}

/**
 * ms_cd - change the working directory 
 *
 * - relative path (a path that starts from the current working directory)
 * - absolute path (a path that starts from the root directory (/) and
 * provides the full location)
 */
int	ms_cd(t_data *data, char **_cmd)
{
	char	*dir;

	if (count_cmd_args(_cmd) == 1 || (count_cmd_args(_cmd) == 2
			&& (ft_strequ(_cmd[1], "~") || ft_strequ(_cmd[1], "--"))))
	{
		dir = env_get_value(data, "HOME");
		if (!dir || !dir[0])
			return (free(dir), ms_error(ERR_CD_NOHOME, NULL, FAILURE, FAILURE));
	}
	else if (count_cmd_args(_cmd) == 2)
	{
		if (ft_strequ(_cmd[1], "-"))
		{
			dir = env_get_value(data, "OLDPWD");
			ft_putendl_fd(dir, STDOUT_FILENO);
		}
		else if (!valid_builtin_args(_cmd[1]))
			return (ms_error(ERR_CD_OPTIONS, NULL, 2, 2));
		else
			dir = ms_set_dir(data, _cmd[1]);
	}
	else
		return (ms_error(ERR_CD_ARGS, NULL, FAILURE, FAILURE));
	return (ms_handle_cd(data, dir));
}
