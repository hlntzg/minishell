#include "./includes/ms.h"

t_env	*env_lstnew(char *key, char *value)
{
	t_env	*new;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = env_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

void	env_add_new(t_data *data, char *key, char *value)
{
	t_env	*new;

	new = env_lstnew(key, value);
	if (!new)
		return ; //(NULL);
	env_lstadd_back(&data->env, new);
}

int	env_lstsize(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{	
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_strcat(char *dest, const char *src)
{
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
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
	i = 0;
	while (tmp)
	{
		envp[i] = malloc(sizeof(char) * (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		ft_strcpy(envp[i], tmp->key);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[size] = NULL;
	return (envp);
}
