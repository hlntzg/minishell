/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:43:03 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/27 16:07:11 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//version 1
void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = sig;
}

//version 2
void	set_heredoc_signal(int signum)
{
	write(1, "\n", 1);
	g_sig = signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

void	handle_sigquit(int signum)
{
	write(2, "Quit (core dumped)\n", 19);
	//g_sig = signum;
	(void) signum;
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
