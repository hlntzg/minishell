#include "main.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*rl;
	pid_t	child_pid;
	int	status;
	char	**cmds;

	while (1)
	{
		rl = readline("my_shell > ");
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
					perror("Failed to execute");
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
