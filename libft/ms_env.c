#include "./includes/ms.h"

int	env_get_key(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_env	*env_get_node(t_data *data, char *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*env_get_value(t_data *data, char  *key)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

int	env_update_value(t_data *data, char *key, char *new_value)
{
	t_env	*node;
	char	*old_value;

	node = env_get_node(data, key);
	if (!node)
		return (1);
	old_value = node->value;
	node->value = new_value;
	free(old_value);
	return (0);
}

static void	set_shell_level(t_data *data)
{
	char	*value;
	int		shlvl;

	value = env_get_value(data, "SHLVL");
	shlvl = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(shlvl);
	env_update_value(data, "SHLVL", ft_itoa(shlvl));
	free(value);
	// check for error atoi, itoa??
}

void	set_environment(t_data *data, char **env)
{
	char	**tmp;
	char	*pwd;

	if (!env || !env[0])
	{
		pwd = getcwd(NULL, 0);
		env_add_new(data, ft_strdup("PWD"), ft_strdup(pwd));
		env_add_new(data, ft_strdup("SHLVL"), ft_strdup("0"));
		env_add_new(data, ft_strdup("_"), ft_strdup("/usr/bin/env"));
		free(pwd);
	}
	else
	{
		while (*env)
		{
			tmp = ft_split(*env, '=');
			env_add_new(data, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
			free(tmp[0]);
			free(tmp[1]);
			free(tmp);
			tmp = NULL;
			env++;
		}
	}
	env_update_value(data, "SHELL", "minishell");
	set_shell_level(data);
	// need to check for malloc errors, return int?
}
