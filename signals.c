/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:34 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/21 15:25:14 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_heredoc(t_data *signal)
{
	static t_data	*data;

	if (!signal)
		data->exit_code = 130;
	else
		data = signal;
}

void	set_signals(void)
{
	rl_done = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

// This function should go in the loop after (pid == 0)
// signals will behave in a default way for child processes
void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// This function will go in the redirection function
// so that heredocs can quit properly.
/*void	heredoc_signal(void)
{
	signal(SIGINT, set_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}*/

void heredoc_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
