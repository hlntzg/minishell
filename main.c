/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2025/01/31 09:47:14 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	g_sig = 0;

char	*set_prompt(t_data *data)
{
	char	*prompt;

	prompt = malloc(sizeof(char) * (ft_strlen("minishell:") + ft_strlen(data->cwd) + ft_strlen("$ ") + 1));
	if (!prompt)
		return (NULL);
    ft_strcpy(prompt, "minishell:");
    ft_strcat(prompt, data->cwd);
    ft_strcat(prompt, "$ ");
    return (prompt);
}

int	update(t_data *data)
{
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
	{
		perror("getcwd() failed");
		return (FAILURE);
	}
	data->prompt = set_prompt(data);
	if (!data->prompt)
	{
		perror("set_prompt() failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	blank_input(char *str)
{
	int	i;

	if (str[0] == '\0' || !str)
		return (1);
	i = 0;
	while (str[i])
	{
		if(!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
			return (0);
		i++;
	}
//	free(str);
	return (1);
}

int main(void)
{
    t_data  data;
	int		status;

	if (!isatty(1) || !isatty(0))
		return (0);
	ft_bzero(&data, sizeof(t_data));	
	set_environment(&data, __environ);
	set_signals();
	printf("\033[1;1H\033[2J");
	status = 0; // outside the loop, right exit code (status) from the main program
	while (1)
	{
		if (update(&data))
			break ;
		data.input_user = readline(data.prompt);
		if (g_sig == SIGINT)
		{
			status = 130;
			data.exit_code = 130;
			g_sig = 0;
		}
		if (data.input_user == NULL) // before exiting, need to clean and free!
            break ;
		if (blank_input(data.input_user))
		{
			free(data.input_user);
			free(data.cwd);
			free(data.prompt);
			continue ;
		}
		add_history(data.input_user);
		if (process_user_input(&data, data.input_user, &status) == SUCCESS)
			ms_execute_newline(&data, &status);
		data.exit_code = status;
		free(data.cwd);
		free(data.prompt);
    }
    rl_clear_history();
	free_and_exit_minishell(&data, status); //ms_free(&data);
    return (status);
}
