/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:12:08 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/29 10:52:34 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_user_input(char *str)
{
	char	*temp;
	t_token	*token;
	//t_tree_node	*tree;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	token = tokenizer(temp);
	parse_tokens(&token);
}

void	init_data(t_data *data)
{
	data->prompt = "minishell$ > ";
}

void	mini_loop(char *str)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);
	init_data(data);
		while (1)
	{	
		//set_signals();
		rl_on_new_line();
		str = readline(data->prompt);
		if (!str)
		{
			printf("exit\n");
			break ;
		}
		add_history(str);
		process_user_input(str);
	}
	rl_clear_history();
}

int	main(void)
{
	char	*rl;
	
	printf("\033[1;1H\033[2J");	/* to clear the terminal and move the cursor 
	to the top-left corner, using ANSI codes */
	rl = NULL;
	mini_loop(rl);	
	return (0);
}
