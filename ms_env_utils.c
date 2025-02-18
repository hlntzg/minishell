/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:43:18 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 09:08:25 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

static char	**free_envp(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	free(envp);
	return (NULL);
}

char	**env_get_array_str(t_data *data)
{
	t_env	*tmp;
	char	**envp;
	int		size;
	int		i;

	tmp = data->env;
	size = env_lstsize(tmp);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = -1;
	while (tmp)
	{
		envp[++i] = malloc(sizeof(char) * (ft_strlen(tmp->key)
					+ ft_strlen(tmp->value) + 2));
		if (!envp[i])
			return (free_envp(envp, i));
		ft_strcpy(envp[i], tmp->key);
		ft_strcat(envp[i], "=");
		if (tmp->value)
			ft_strcat(envp[i], tmp->value);
		tmp = tmp->next;
	}
	envp[size] = NULL;
	return (envp);
}

char	**exe_get_path(char **envp)
{
	char	**path;
	char	*cwd;
	char	*tmp;

	path = NULL;
	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		tmp = strdup(cwd);
		free(cwd);
		if (!tmp)
			return (NULL);
		path = ft_split(tmp, ':');
		free(tmp);
		return (path);
	}
	path = ft_split((*envp) + 5, ':');
	if (!path)
		return (NULL);
	return (path);
}
