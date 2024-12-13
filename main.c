/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/12/13 17:24:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

char	*set_prompt(t_data *data)
{
	char	*prompt;

	prompt = ft_strjoin("minishell:", data->cwd);
	if (!prompt)
		return (NULL);
	prompt = ft_strjoin(prompt, "$ ");
	if (!prompt)
		return (NULL);
	return (prompt);
}

int main(void)
{
    t_data  data;
/*	char	**e;*/

	if (!isatty(1) || !isatty(0))
		return (0);
	data.env = NULL;
	set_environment(&data, __environ);
/*	int i = 0;
	e = exe_get_path(env_get_array_str(&data));
	while (e[i])
	{	
		printf("[%d] %s\n", i, e[i]);
		i++;
	}*/
	//set_signals();
	printf("\033[1;1H\033[2J");
	while (1)
	{
		data.cwd = getcwd(NULL, 2048);
		data.prompt = set_prompt(&data);
		rl_on_new_line();
		data.input_user = readline(data.prompt);
        if (!data.input_user)
        {
            printf("exit\n");
            break ;
        }
        add_history(data.input_user);
    }
    rl_clear_history();
    return (0);
}
