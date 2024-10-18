/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_natalie.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:23:59 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/18 12:44:37 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <signal.h>

void	handle_sigquit(int sig)
{
	(void)sig;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*rl;
	pid_t	child_pid;
	int	status;
	char	**cmds;
	struct	sigaction	sa;

	while (1)
	{
		rl = readline("my_shell > ");
		sa.sa_handler = handle_sigquit;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGQUIT, &sa, NULL);
		child_pid = fork();
		{
			if (child_pid == -1)
			{
				perror("Failed to create child process");
				exit(EXIT_FAILURE);
			}
			if (child_pid == 0)
			{
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

