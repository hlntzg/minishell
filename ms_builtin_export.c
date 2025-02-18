/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:28:28 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/05 11:40:42 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

static bool	invalid_export_variable(char *str)
{
	int	i;

	i = 1;
	if ((str[0] != '_') && !ft_isalpha(str[0]))
		return (true);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if ((str[i] != '_') && !ft_isalnum(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static bool	any_invalid_export_variable(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (invalid_export_variable(str[i]))
			return (true);
		i++;
	}
	return (false);
}

char	**get_key_value(char *str)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp[0] = malloc(sizeof(char) * i + 1);
	if (!tmp[0])
		return (NULL);
	ft_strncpy(tmp[0], str, i);
	tmp[0][i] = '\0';
	j = i + 1;
	while (str[j])
		j++;
	tmp[1] = malloc(sizeof(char) * (j - i));
	if (!tmp[1])
		return (NULL);
	ft_strncpy(tmp[1], str + i + 1, j - i - 1);
	tmp[1][j - i - 1] = '\0';
	tmp[2] = NULL;
	return (tmp);
}

/*variable: if (KEY) else (KEY= or KEY=value) */
static void	ms_handle_export(t_data *data, char *variable)
{
	char	**tmp;

	if (ft_strchr(variable, '=') == NULL)
	{
		if (env_get_key(data, variable))
			return ;
		env_add_new(data, ft_strdup(variable), NULL);
	}
	else
	{
		tmp = get_key_value(variable);
		if (env_get_key(data, tmp[0]))
			env_update_value(data, tmp[0], ft_strdup(tmp[1]));
		else
			env_add_new(data, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		tmp = NULL;
	}
}

/**
 * exporting new variables ...
 * key: must start with a letter (A-Z, a-z) or an underscore (_), after the 
 * first character, the name can contain only letters, digits (0-9), and
 * underscores.
 * value: can contain any characters.
 */
int	ms_export(t_data *data, char **_cmd, int *_out)
{
	int	status;
	int	i;

	if (count_cmd_args(_cmd) == 1)
		return (builtins_print_export_variables(data, _out[1]), SUCCESS);
	if (_cmd[1] && !valid_builtin_args(_cmd[1]))
		return (ms_error(ERR_EXP_OPTIONS, NULL, 2, 2));
	if (data->processes)
	{
		if (any_invalid_export_variable(_cmd))
			return (ms_error(ERR_EXP_BAD_KEY, NULL, 1, 1));
		return (0);
	}
	status = 0;
	i = 1;
	while (_cmd[i])
	{
		if (invalid_export_variable(_cmd[i]))
			status = ms_error(ERR_EXP_BAD_KEY, NULL, 1, 1);
		else
			ms_handle_export(data, _cmd[i]);
		i++;
	}
	return (status);
}
