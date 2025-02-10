/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:16:04 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/10 16:27:50 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

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
		free_ast(data->tree);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free_pid(data);

	data->exit_code = status;
}

void	ms_free_and_exit_child(t_data *data, int status)
{
	if (data->input_user == NULL)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (data->env)
		free_env(data);
	if (data->tree)
		free_ast(data->tree);
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

void	free_and_exit_minishell(t_data *data, int status)
{
	if (data->input_user == NULL)
		ft_putendl_fd("exit", STDOUT_FILENO);

	if (data->env)
		free_env(data);
	if (data->cwd)
		free(data->cwd);
	if (data->prompt)
		free(data->prompt);
	if (data->envp)
		free_char_double_ptr(&data->envp);
	if (data->envp_path)
		free_char_double_ptr(&data->envp_path);
	if (data->pid)
		free_pid(data);
	exit (status);
}
