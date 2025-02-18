/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/14 10:28:14 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"

int	g_sig = 0;

char	*set_prompt(t_data *data)
{
	char	*prompt;
	size_t	len1;
	size_t	len2;

	prompt = NULL;
	len1 = ft_strlen("minishell:");
	len2 = 1;
	if (data->cwd != NULL)
		len2 = ft_strlen(data->cwd);
	prompt = malloc(sizeof(char) * (len1 + len2 + ft_strlen("$ ") + 1));
	if (!prompt)
		return (NULL);
	ft_strcpy(prompt, "minishell:");
	if (data->cwd)
		ft_strcat(prompt, data->cwd);
	ft_strcat(prompt, "$ ");
	return (prompt);
}

int	update(t_data *data)
{
	data->cwd = getcwd(NULL, 0);
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
		if (!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
			return (0);
		i++;
	}
	return (1);
}

int	minishell_loop(t_data *data, int status)
{
	while (1)
	{
		if (update(data))
			break ;
		data->input_user = readline(data->prompt);
		if (g_sig == SIGINT)
		{
			status = 130;
			g_sig = 0;
		}
		if (!data->input_user)
			break ;
		if (blank_input(data->input_user))
		{
			free(data->input_user);
			free_prompt(data);
			continue ;
		}
		add_history(data->input_user);
		if (process_user_input(data, data->input_user, &status) == SUCCESS)
			ms_execute_newline(data, &status);
		else
			free_prompt(data);
	}
	return (status);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		status;

	(void) argv;
	if (argc != 1)
		return (ms_error(argv[1], ERR_NO_FILE_OR_DIR, 127, 127));
	if (!isatty(1) || !isatty(0))
		return (0);
	ft_bzero(&data, sizeof(t_data));
	set_environment(&data, __environ);
	set_signals();
	printf("\033[1;1H\033[2J");
	status = minishell_loop(&data, 0);
	rl_clear_history();
	free_and_exit_minishell(&data, status);
	return (0);
}
