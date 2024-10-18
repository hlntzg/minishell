#include "main.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*rl;
	pid_t	child_pid;
	int	status;
	char	**cmds;
	char	*abs_path;
	
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
			cmds = ft_split(rl);
			abs_path = get_file_path(cmds[0]);
			if (child_pid == 0)
			{
				if (execve(abs_path, cmds, NULL) == -1)
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
	free(abs_path);
	return (0);
}
