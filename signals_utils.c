/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:43:03 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/09 15:38:01 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	//printf("parent signal handler\n");
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = sig;
}

void	set_heredoc_signal(int signum)
{
	//printf("\nheredoc signal handler\n");
	write(1, "\n", 1);
	g_sig = signum;
	close(STDIN_FILENO);
//	exit (130); not exit here because we need to free child before!
}

void	handle_sigquit(int signum)
{
	write(2, "Quit (core dumped)\n", 19);
	g_sig = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

void	handle_sigint_exe(int signum)
{
	write(1, "\n", 1);
	g_sig = signum;
}

void	heredoc_sigint_exe(int signum)
{
//	write(1, "\0", 1);
	g_sig = signum;
}
/*
//version 1
void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//version 2
void	set_heredoc_signal(int signum)
{
	(void)signum;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
	exit (g_sig);
}

void	handle_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_sig = signum;
	}
}

void	handle_sigint_exe(int signum)
{
	write(1, "\n", 1);
	g_sig = signum;
	//g_sig = SIGINT;
}*/
