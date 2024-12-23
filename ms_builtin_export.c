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

static bool any_invalid_export_variable(char **str)
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

/*variable: KEY=Value, KEY or KEY= */
static void	ms_handle_export(t_data *data, char *variable)
{
	(void) data;
	char	**tmp;

	if (ft_strchr(variable, '=') == NULL)
	{
		if (env_get_key(data, variable)) // if exists, do nothing
			return ;
		env_add_new(data, ft_strdup(variable), NULL);
	}
	else
	{
		tmp = get_key_value(variable);
		if (env_get_key(data, tmp[0]))
			env_update_value(data, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
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
 * first character, the name can contain only letters, digits (0-9), and underscores.
 * value: can contain any characters.
 */
int		ms_export(t_data *data, t_cmd *cmd)
{
	int	i;

	if (data->total_cmds == 1 && arguments_count(cmd->args) == 1)
		return (builtins_print_export_variables(data, 1), SUCCESS);
	if (!valid_builtin_args(cmd->args[1]))
		return (ft_putendl_fd(ERR_EXP_OPTIONS, STDERR_FILENO), FAILURE);
	if (data->total_cmds > 1)
	{
		if (any_invalid_export_variable(cmd->args))
			ft_putendl_fd(ERR_EXP_BAD_KEY, STDERR_FILENO);
		exit(FAILURE);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (invalid_export_variable(cmd->args[i]))
			return (ft_putendl_fd(ERR_EXP_BAD_KEY, STDERR_FILENO), FAILURE);
		else
			ms_handle_export(data, cmd->args[i]);
		i++;
	}
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
