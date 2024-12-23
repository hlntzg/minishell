#include "./includes/ms.h"

char	*ms_getpwd(t_data *data)
{
	return (env_get_value(data, "PWD"));
}

int	ms_pwd(t_data *data, t_cmd *cmd)
{
	char	*cwd;

	(void) cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ms_getpwd(data);
		if (!cwd || *cwd == '\0')
		{
            ft_putendl_fd("Error: Unable to retrieve current directory", 2);
            return (-1);  // Return error if both getcwd and PWD fail
        }
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
