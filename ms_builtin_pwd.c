#include "./includes/ms.h"

char	*ms_getpwd(t_data *data)
{
	return (env_get_value(data, "PWD"));
}

int	ms_pwd(t_data *data, char **_cmd, int *_out)
{
	char	*cwd;

	if (_cmd[1] && !valid_builtin_args(_cmd[1]))
	{
		data->exit_code = 2;
		return (ft_putendl_fd(ERR_PWD_OPTIONS, STDERR_FILENO), FAILURE);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ms_getpwd(data);
		if (!cwd || *cwd == '\0')
		{
			ft_putendl_fd("Error: Unable to retrieve current directory", 2);
			return (-1);// Return error if both getcwd and PWD fail
		}
	}
	ft_putendl_fd(cwd, _out[1]);
	free(cwd);
	return (SUCCESS);
}
