/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2025/01/14 14:53:47 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

char	*set_prompt(t_data *data)
{
	char	*prompt;

	prompt = malloc(sizeof(char) * (ft_strlen("minishell") + ft_strlen(data->cwd) + ft_strlen("$ ") + 1));
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

int main(void)
{
    t_data  data;

	if (!isatty(1) || !isatty(0))
		return (0);
	ft_bzero(&data, sizeof(t_data));	
	set_environment(&data, __environ);
	set_signals();
	printf("\033[1;1H\033[2J");
	while (1)
	{
		if (update(&data))
		{
		//	ms_free(&data);
			break ;
		}
		rl_on_new_line();
		data.input_user = readline(data.prompt);
		if (data.input_user == NULL)
    	{
            printf("exit of EOF \n");
            exit (EXIT_SUCCESS);
        }
        if (data.input_user[0] == '\0')
			continue ;
		add_history(data.input_user);
		if (!data.input_user)
            break ;
		else
		{
			if (process_user_input(&data, data.input_user) == SUCCESS)
				ms_execute_newline(&data);
//			ms_free(&data);
//			ms_reset(&data);
		}
    }
    rl_clear_history();
    return (0);
}
