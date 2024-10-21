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

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	disable_quit_signal(void)
{
	struct termios	term_settings;

	if (tcgetattr(STDIN_FILENO, &term_settings) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term_settings.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_settings) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	set_signals(void)
{
	disable_quit_signal();
	signal(SIGINT, handle_sigint);
}
