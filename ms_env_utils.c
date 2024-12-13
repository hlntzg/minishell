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
