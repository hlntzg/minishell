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

void	process_user_input(t_data *data, char *str)
{
	char	*temp;
	t_token	*token;
	t_tree_node	*tree;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	if (temp == NULL)
	{
		// handle error
		return ;
	}
	token = tokenizer(temp);
	//printf("Token created: type=%d, content=%s\n", token->type, token->content);
	if (token == NULL)
	{
		//handle error
		return ;
	}
	tree = parse_tokens(&token);
	if (tree == NULL)
	{
		//handle error
		return ;
	}
	execute_newline(data, tree);
	//expand_env_variables()
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
		process_user_input(data, str);
	}
	rl_clear_history();
}

//my main
/*int	main(void)
{
	char	*rl;
	//t_data	data;

	if (!isatty(1) || !isatty(0))
		return (0);
	//data.env = NULL;
	//set_environment(&data, __environ);
	printf("\033[1;1H\033[2J");
	rl = NULL;
	mini_loop(rl);
	return (0);
}*/

//test main #2
int main(void)
{
    printf("\033[1;1H\033[2J"); // Clear screen
    test_parser();
    return 0;
}

/*
Helena's main
int main(void)
{
    t_data  data;
//	char	**e;

	if (!isatty(1) || !isatty(0))
		return (0);
	data.env = NULL;
	set_environment(&data, __environ);
	int i = 0;
	e = exe_get_path(env_get_array_str(&data));
	while (e[i])
	{	
		printf("[%d] %s\n", i, e[i]);
		i++;
	}
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
} */
