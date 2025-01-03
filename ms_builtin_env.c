#include "./includes/ms.h"

/**
 * env - Builtin env function
 *
 * If no argument or option is specify, the function prints env variables.
 * Otherwise, it return error and display an error message.
 * 
 * NOTE: do not accept redirections, fd set to 1 for now
 */
int ms_env(t_data *data, char **_cmd)
{
	if (_cmd[1])
	{
		if (data->total_cmds == 1)
			return (ft_putendl_fd(ERR_ENV_ARGS, STDERR_FILENO), 1); // error
		exit (EXIT_FAILURE); // error
	}
	builtins_print_env_variables(data, 1); // will print in STDOUT_FILENO now
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
