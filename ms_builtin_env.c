#include "./includes/ms.h"

/**
 * env - Builtin env function
 *
 * If no argument or option is specify, the function prints env variables.
 * Otherwise, it return error and display an error message.
 * 
 */
int ms_env(t_data *data, char **_cmd, int *_out)
{
	if (_cmd[1])
	{
		if (_cmd[1][0] == '-')
		{
			ms_error(ERR_ENV_OPTIONS, NULL, 125, FAILURE);
			data->exit_code = 125;
		}
		else
		{
			ms_error(ERR_ENV_ARGS, NULL, 127, FAILURE);
			data->exit_code = 127;
		}
		return (SUCCESS);
	}
	builtins_print_env_variables(data, _out[1]);
	data->exit_code = 0;
	return (SUCCESS);
}
