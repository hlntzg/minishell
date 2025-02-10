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
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = sig;
}

void	set_heredoc_signal(int signum)
{
	write(1, "\n", 1);
	g_sig = signum;
	close(STDIN_FILENO);
}

void	handle_sigint_exe(int signum)
{
	write(1, "\n", 1);
	g_sig = signum;
}

/*void	heredoc_sigint_exe(int signum)
{
	write(1, "\0", 1);
	g_sig = signum;
}*/
