/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:16:23 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/13 10:30:28 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_prompt(t_data *data)
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
			ast->value[i] = NULL;
			i++;
		}
		free(ast->value);
		ast->value = NULL;
	}
	free_ast(ast->left);
	free_ast(ast->right);
	free(ast);
	ast = NULL;
}
