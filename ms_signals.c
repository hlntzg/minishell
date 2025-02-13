/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/13 08:57:45 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "./includes/ms.h"

void	set_signals(void)
{
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
void	heredoc_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, set_heredoc_signal);
}

void	restore_main_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
