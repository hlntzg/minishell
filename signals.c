/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/04 13:25:15 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
/*
void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}*/

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
void	heredoc_signal(void)
{
	signal(SIGINT, set_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}

/*void	heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = set_heredoc_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}*/

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void    restore_main_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
