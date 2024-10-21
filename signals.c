/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:18:34 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/21 14:47:35 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_sigint(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\nmy_shell > ", 12);
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
