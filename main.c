/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:21:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/11/25 14:33:24 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		        /* readline */
#include <readline/readline.h>	/* readline */
#include <readline/history.h>	/* readline */

typedef struct  s_data
{
    char    *prompt;
}   t_data;

int main(void)
{
    char    *rl;
    t_data  data;

    data.prompt = "prompt > ";
    printf("\033[1;1H\033[2J");	/* to clear the terminal and move the cursor to the top-left corner, using ANSI codes */
	while (1)
	{
        rl_on_new_line();
        rl = readline(data.prompt);
        if (!rl)
        {
            printf("exit\n");
            break ;
        }
        add_history(rl);
    }
    rl_clear_history();
    return (0);
}
