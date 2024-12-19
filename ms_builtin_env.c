#include "./includes/ms.h"

/**
 * env - Builtin env function
 *
 * If no argument or option is specify, the function prints env variables.
 * Otherwise, it return error and display an error message.
 * 
 * NOTE: do not accept redirections, fd set to 1 for now
 */
int env(t_data *data, t_cmd *cmd)
{
	(void) data;
	
	if (cmd->args[1])
	{
		if (data->total_cmds == 1)
			return (ft_putendl_fd(ERROR_ENV_ARGS, STDERR_FILENO), 1); // error
		exit (EXIT_FAILURE); // error
	}
	builtins_print_env_variables(data, 1);
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
