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

int	main(void)
{
	char	*rl;
	//t_data	*data;
	//t_token	*token;
	//t_tree_node	*tree;

//	init_data(data);	
	printf("\033[1;1H\033[2J");	/* to clear the terminal and move the cursor 
	to the top-left corner, using ANSI codes */
	while (1)
	{	
		//set_signals();
		rl_on_new_line();
		rl = readline("my prompt");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}
		add_history(rl);
		tokenizer(rl);
		/*need to add some checks in here and probably need a 
		new function for this part*/
		//tree = ft_parse_tokens(&token);
	}
	rl_clear_history();
	return (0);
}
