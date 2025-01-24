/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/24 11:37:30 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*void	quit_heredoc(int signal, t_data *data)
{
	if (signal != SIGINT)
		return ;
	data->exit_code = 130;
	printf("\n");
}*/

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	//signal(SIGPIPE, SIG_IGN);
}

// This function should go in the loop after (pid == 0)
// signals will behave in a default way for child processes
void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	//signal(SIGPIPE, SIG_IGN);
}

// This function will go in the redirection function
// so that heredocs can quit properly.
/*void	heredoc_signal(void)
{
	signal(SIGINT, quit_heredoc);
	signal(SIGQUIT, SIG_IGN);
}*/
