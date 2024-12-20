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

/*variable: KEY=Value, KEY or KEY= */
void	ms_handle_export(t_data *data, char *variable)
{
	(void) data;
	char	*key;
	//char	*value;

	// KEY		if exist, do nothing,				if doesnt add_it_new_var
	if (ft_strchr(variable, '=') == NULL)
	{
		if (env_get_key(data, variable)) // if exists, do nothing
			return ;
		env_add_new(data, ft_strdup(variable), NULL);
	}
	else
	{
		int i = 0;
		while (variable[i] != '=')
			i++;
		key = malloc(sizeof(char) * i);
		if (!key)
			return ;
		key = ft_strncpy(key, variable, i);
	//	value = &variable[i + 1];
		if (env_get_key(data, key))
			env_update_value(data, key, &variable[i + 1]);
		else
			env_add_new(data, key, ft_strdup(&variable[i + 1]));
		// should it free key, and the ft_strdup?
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
	if (data->total_cmds == 1 && !valid_builtin_args(cmd->args[1]))
		return (ft_putendl_fd(ERR_EXP_OPTIONS, STDERR_FILENO), EXIT_FAILURE);
	if (data->total_cmds > 1)
	{
		if (any_invalid_export_variable(cmd->args))
			ft_putendl_fd(ERR_EXP_BAD_KEY, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (invalid_export_variable(cmd->args[i]))
			return (ft_putendl_fd(ERR_EXP_BAD_KEY, STDERR_FILENO), EXIT_FAILURE);
		else
			ms_handle_export(data, cmd->args[i]);
		i++;
	}
	if (data->total_cmds == 1)
		return (SUCCESS);
	exit (SUCCESS);
}
