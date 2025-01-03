#include "./includes/ms.h"

/**
 * ms_set_dir - Constructs the absolute path for a relative directory
 *
 */
char	*ms_set_dir(t_data *data, char *dir)
{
    char	*tmp;
    char	*pwd;
	char	*new_dir;

    if (dir[0] != '/')
    {
        tmp = ft_strjoin("/", dir);
        pwd = ms_getpwd(data);
        new_dir = ft_strjoin(pwd, tmp);
        free(tmp);
        free(pwd);
        return (new_dir);
    }
    return (ft_strdup(dir));
}

void	ms_update_oldpwd(t_data *data, char *old_cwd)
{
	env_update_value(data, "OLDPWD", old_cwd);
}

void	ms_update_pwd(t_data *data, char *new_cwd)
{
	env_update_value(data, "PWD", new_cwd);
}

/**
 * ms_cd - change the working directory 
 *
 * - relative path (a path that starts from the current working directory)
 * - absolute path (a path that starts from the root directory (/) and provides the full location)
 */
int	ms_cd(t_data *data, t_cmd *cmd)
{
	char	*dir;
	char	*old_pwd;
	
	// if there is no "PWD" or "PWD"?
	if (arguments_count(cmd->args) == 1)
	{
		dir	= env_get_value(data, "HOME");
		if (!dir || !dir[0])
			return (ft_putendl_fd(ERR_CD_NOHOME, STDERR_FILENO), FAILURE);
	}
	else if (arguments_count(cmd->args) == 2)
	{
		if (!valid_builtin_args(cmd->args[1]))
			return (ft_putendl_fd(ERR_CD_OPTIONS, STDERR_FILENO), ERR_CMD_LINE); // invalid option is exit code 2
		dir = ms_set_dir(data, cmd->args[1]);//	dir = cmd->args[1];
	}
	else
		return (ft_putendl_fd(ERR_CD_ARGS, STDERR_FILENO), FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(dir);
		if (data->total_cmds == 1)
			return (ft_putendl_fd(strerror(errno), STDERR_FILENO), FAILURE); // Error handling
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit (FAILURE);
	}
	ms_update_oldpwd(data, ft_strdup(old_pwd));
	ms_update_pwd(data, getcwd(NULL, 0));
	free(old_pwd);
	free(dir);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
