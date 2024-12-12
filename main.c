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

void	init_data(t_data *data)
{
	data->prompt = "minishell$ > ";
}

void	mini_loop(char *str)
{
	char	temp;
	t_data	*data;
	t_token	*token;

	init_data(data);
	temp = NULL;
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
		temp = ft_strtrim(str, " \t\n\v\f\r");
		token = tokenizer(temp);
		/*if (token)
		{
			tree = parse_tokens(&token);
		}*/
		/*need to add some checks in here and probably need a 
		new function for this part*/
		//tree = ft_parse_tokens(&token);
	}
	rl_clear_history();
}

int	main(void)
{
	char	*rl;
	//t_token	*token;
	//t_tree_node	*tree;

	printf("\033[1;1H\033[2J");	/* to clear the terminal and move the cursor 
	to the top-left corner, using ANSI codes */
	mini_loop(rl);	
	return (0);
}
