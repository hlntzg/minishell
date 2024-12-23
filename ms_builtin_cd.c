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

int	ms_cd(t_data *data, t_cmd *cmd)
{
	char	*dir;
	char	*old_pwd;
	
	if (arguments_count(cmd->args) == 1)
	{
		dir	= env_get_value(data, "HOME");
		if (!dir || !dir[0])
			return (ft_putendl_fd(ERR_CD_NOHOME, STDERR_FILENO), EXIT_FAILURE);
	}
	else if (arguments_count(cmd->args) == 2)
	{
		if (!valid_builtin_args(cmd->args[1]))
			return (ft_putendl_fd(ERR_CD_OPTIONS, STDERR_FILENO), 2); // invalid option is exit code 2
		dir = ms_set_dir(data, cmd->args[1]);//	dir = cmd->args[1];
	}
	else
		return (ft_putendl_fd(ERR_CD_ARGS, STDERR_FILENO), EXIT_FAILURE);
	old_pwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(dir);
		if (data->total_cmds == 1)
			return (ft_putendl_fd(strerror(errno), STDERR_FILENO), EXIT_FAILURE); // Error handling
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	// if there is no "PWD" ?
	ms_update_oldpwd(data, ft_strdup(old_pwd));
	ms_update_pwd(data, getcwd(NULL, 0));
	free(old_pwd);
	free(dir);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
