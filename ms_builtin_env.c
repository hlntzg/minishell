/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:17:17 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/05 11:26:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

/**
 * env - Builtin env function
 *
 * If no argument or option is specify, the function prints env variables.
 * Otherwise, it return error and display an error message.
 * 
 */
int	ms_env(t_data *data, char **_cmd, int *_out)
{
	if (_cmd[1])
	{
		if (_cmd[1][0] == '-')
			return (ms_error(ERR_ENV_OPTIONS, NULL, 125, 125));
		else
			return (ms_error(ERR_ENV_ARGS, NULL, 127, 127));
	}
	builtins_print_env_variables(data, _out[1]);
	return (SUCCESS);
}
