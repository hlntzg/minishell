/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:30:09 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/21 14:46:43 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char **tmp_parsing)
{
	int	i = 1;

	while (tmp_parsing[i])
	{
		ft_putstr_fd(tmp_parsing[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}

int	main(void)
{
	char	*rl;
	char	**tmp_parsing;

//	init_data();	
	printf("\033[1;1H\033[2J");	/* to clear the terminal and move the cursor to the top-left corner, using ANSI codes */
	while (1)
	{
		set_signals();
		rl_on_new_line();
		rl = readline("prompt > ");
		if (!rl)
			break ;
		tmp_parsing = ft_split(rl, ' ');	
		if (ft_strequ(tmp_parsing[0], "echo") == 1)
			ms_echo(tmp_parsing);
		add_history(rl);
	}
	rl_clear_history();
	return (0);
}
