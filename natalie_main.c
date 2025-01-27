/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   natalie_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2025/01/27 10:59:14 by nmeintje         ###   ########.fr       */
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

void	null_input(t_data data)
{
	if (data.input_user == NULL)
    {
        printf("exit of EOF \n");
        exit (data.exit_code);
    }
    //else if (data.input_user[0] == '\0')
	//{
		//free(data.input_user);
		//break ;
	//}
}
			
int	shell_loop(t_data data)
{
	while (1)
	{
		set_signals();
		if (update(&data))
			break ;
		data.input_user = readline(data.prompt);
		if (g_sig == SIGINT)
		{
			data.exit_code = 130;
			g_sig = 0;
		}
		if (!data.input_user)
            continue ;
		if (data.input_user == NULL || data.input_user[0] == '\0')
				null_input(data);
		add_history(data.input_user);
		if (process_user_input(&data, data.input_user) == SUCCESS)
			ms_execute_newline(&data);
		free(data.input_user);
    }
	return (1);
}

int	main(void)
{
	t_data	data;
	int	status;

	if (!isatty(1) || !isatty(0))
		return (0);
	ft_bzero(&data, sizeof(t_data));	
	set_environment(&data, __environ);
	printf("\033[1;1H\033[2J");
	status = shell_loop(data);
	rl_clear_history();
	return (status);
}
