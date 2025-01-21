/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2025/01/21 15:57:18 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

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
		if (!ft_isprint(str[i]) && ft_iswhitespace(str[i]))
			return (1);
		i++;
	}
	return (0);

}

int main(void)
{
    t_data  data;
	int	status;

	if (!isatty(1) || !isatty(0))
		return (0);
	ft_bzero(&data, sizeof(t_data));	
	set_environment(&data, __environ);
	set_signals();
	printf("\033[1;1H\033[2J");
	while (1)
	{
		status = 0;
		if (update(&data))
		{
		//	ms_free(&data);
			break ;
		}
		rl_on_new_line();
		data.input_user = readline(data.prompt);
		if (data.input_user == NULL) // before exiting, need to clean and free!
    	{
            printf("exit of EOF \n");
            exit (EXIT_SUCCESS);
        }
        if (blank_input(&data.input_user[0]))
			continue ;
		add_history(data.input_user);
		if (!data.input_user) // data.input_user == NULL
            break ;
		else if (!status)
		{
			if (process_user_input(&data, data.input_user) == SUCCESS)
				ms_execute_newline(&data, &status);
		}
		data.exit_code = status;
    }
    rl_clear_history();
    return (0);
}
