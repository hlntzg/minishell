#include "./includes/ms.h"

void	free_char_double_ptr(char ***ptr)
{
	int	i;

	if (ptr == NULL || *ptr == NULL)
		return ;
	i = 0;
	while ((*ptr)[i] != NULL)
	{
		free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
    }
	free(*ptr);
	*ptr = NULL;
}


void	free_env(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		tmp = data->env->next;
		//if (data->env->key && data->env->key[0] != '\0')
		//	free(data->env->key);
	//	printf("Freeing key: %s\n", data->env->key);
		free(data->env->key);
	//	printf("Freeing value: %s\n", data->env->value);
		free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
}

void	ms_free(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->cwd)
		free(data->cwd);
	if (data->input_user)
		free(data->input_user);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free(data->pid);
	if (data->env)
		free_env(data);
//	if (data->fd)
//		free(data->fd);
}

void	free_and_exit_minishell(t_data *data, int status)
{
	(void) data;
	if (data->input_user == NULL)
		ft_putendl_fd("exit from free_and_exit_minishell", 2);
//	printf("free everyhing and exit with code %d\n", status);

	if (data->env)
		free_env(data);
/*	if (data->tree)
		free_ast_tree();*/
	if (data->prompt)
		free(data->prompt);
	if (data->cwd)
		free(data->cwd);
	if (data->input_user)
		free(data->input_user);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free(data->pid);
	exit (status);
}

/*  old stuff
void	ms_reset(t_data *data)
{
	data->prompt = NULL;
	data->cwd = NULL;
	data->input_user = NULL;
	data->envp = NULL;
	data->envp_path = NULL;
	data->total_cmds = 0;
	data->total_process = 0;
	data->pid = NULL;
	data->fd = NULL;
}*/
