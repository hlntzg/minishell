/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_natalie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:23:59 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/18 14:59:06 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <signal.h>
#include <termios.h>

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_sigaction(int	signum)
{
	struct	sigaction	sa;
	struct termios term_settings;

	sa.sa_handler = handle_sigquit;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(signum, &sa, NULL) == -1)
	{
		perror("Failed to set up signal handler\n");
		exit(EXIT_FAILURE);
	}
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

int main(void)
{
	char	*rl;
	pid_t	child_pid;
	int	status;
	char	**cmds;
	
	setup_sigaction(SIGQUIT);
	while (1)
	{
		rl = readline("my_shell > ");
		if (rl == NULL)
		{
			printf("exit\n");
			exit (EXIT_SUCCESS);
		}
		child_pid = fork();
		{
			if (child_pid == -1)
			{
				perror("Failed to create child process");
				exit(EXIT_FAILURE);
			}
			if (child_pid == 0)
			{
				signal(SIGQUIT, SIG_IGN);
				cmds = ft_split(rl);
				if (execve(cmds[0], cmds, NULL) == -1)
				{
					perror("myFailed to execute");
					exit(EXIT_FAILURE);
				}
				//printf("Successful child process running <%s>\n", rl);
			}
			else
				wait(&status);	
		}
	}
	free(rl);
	return (0);
}

