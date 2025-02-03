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

	if (!data || !data->env)
		return ;
	while (data->env)
	{
		tmp = data->env->next;
		free(data->env->key);
		free(data->env->value);
		free(data->env);
		data->env = tmp;
	}
	data->env = NULL;
}

void	free_pid(t_data *data)
{
	if (data && data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
}

/*
void	free_ast(t_tree_node *ast)
{
	int	i;

	if (!ast)
		return ;
	i = 0;
	if (ast->value)
	{
		while (ast->value[i])
		{ 
			free(ast->value[i]);
			i++;
		}
		free(ast->value);

	}
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
}*/

void free_ast(t_tree_node **ast)
{
    int i;

    if (!ast || !*ast)
        return;

    i = 0;
    if ((*ast)->value)
    {
        while ((*ast)->value[i])
        {
            free((*ast)->value[i]);
			(*ast)->value[i] = NULL;
            i++;
        }
        free((*ast)->value);
		(*ast)->value = NULL;
    }

    free_ast(&((*ast)->left));
    free_ast(&((*ast)->right));

    free(*ast);
    *ast = NULL; // Prevent dangling pointer
}

void	update_minishell(t_data *data, int status)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->cwd)
	{
		free(data->cwd);
		data->cwd = NULL;
	}
	if (data->tree)
		free_ast(&data->tree);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free_pid(data);

	data->exit_code = status;
}

void	free_and_exit_minishell(t_data *data, int status)
{
	if (data->input_user == NULL)
		ft_putendl_fd("exit from free_and_exit_minishell", 2);

	if (data->env)
		free_env(data);
/*	if (data->tree)
		free_ast(data->tree);*/
	if (data->cwd)
		free(data->cwd);
	if (data->prompt)
		free(data->prompt);
//	if (data->input_user) //we dont allocate memory for this!
//		free(data->input_user);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free_pid(data);
	exit (status);
}

void	ms_free_and_exit_child(t_data *data, int status)
{
	if (data->input_user == NULL)
		ft_putendl_fd("exit from free_and_exit_minishell", 2);
	if (data->env)
		free_env(data);
	if (data->tree)
		free_ast(&data->tree);
	if (data->cwd)
	{
		free(data->cwd);
		data->cwd = NULL;
	}
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free_pid(data);
	exit (status);

}
