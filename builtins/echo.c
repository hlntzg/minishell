#include <unistd.h>		// For write
#include <stdbool.h>	// For bool, true, false

// libft
static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

// libft
static int	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		str = "(null)";
	if (write(fd, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

static bool	valid_echo_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || !str[1])
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

// do not accept redirections, fd set to 1 for now
int	ft_echo(char **token)
{
	int	i;
	int	op_n;

	i = 1;
	op_n = 0;
	if (token[0] && token[1] && valid_echo_option(token[1]))
		op_n = 1;
	i += op_n;
	while (token[i] && valid_echo_option(token[i]))
		i++;
	while (token[i]) // Output arguments if there is any
	{
		ft_putstr_fd(token[i], 1);
		if (token[++i]) // If there are more arguments, write a space between them
			write(1, " ", 1);
	}
	if (!token[i] || !op_n)
		write(1, "\n", 1);
	return (0);
}

// main
#include <string.h> 
#include <stdio.h>

int main(int argc, char **argv)
{
	(void)argc;
	if (strcmp(argv[1], "echo") == 0)
	{
		argv++;
		return (ft_echo(argv));
	}
	return (1);
}
