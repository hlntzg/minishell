#define EXIT_MANY_ARGS "too many arguments\n"		// exit_code = 1, do not exit
#define EXIT_BAD_ARG "numeric argument required\n"	// exit_code = 2, exit

#include <unistd.h>		// For write
#include <stdbool.h>	// For bool, true, false
#include <limits.h>		// 
#include <stdlib.h>		// Exit

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
// libft
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// libft
static long	ft_atol(const char *str)
{
	long		sign = 1;
    long long	result = 0;
    int			i = 0;

    while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (result > (LONG_MAX - (str[i] - '0')) / 10)
        {
            if (sign == 1)
                return (LONG_MAX);
            else
                return (LONG_MIN);
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (sign * result);
}

// libft
int	ft_atoi(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
		if (result < 0 && sign == 1)
			return (-1);
		else if (result < 0 && sign == -1)
			return (0);
	}
	return ((int)(result * sign));
}

/**
 * error_message_exit - Prints an error message to stderr
 *
 * @error: The error message to be printed
 * @arg: Optional argument related to the error (can be NULL)
 * 
 * This function prints a formatted error message related to the builtin exit 
 * function to stderr (file descriptor 2). It prepends "minishell: exit: "
 * to the message and the following message behaves like in bash.
 */
static void	error_message_exit(char *error, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error, 2);
}

/** 
 * invalid_exit_arg - Checks if the given string is a valid exit argument.
 *
 * valid: 123 -266 +22 999999
 * invalid: abc 1h3ll@ 172981720972901902102912801
 *
 * Return: true if the string is invalid; false if valid.
 */
static bool	invalid_exit_arg(char *str)
{
	int	i;
	
	if (!str || ft_atol(str) <= LONG_MIN || ft_atol(str) >= LONG_MAX)
		return (true);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * ft_exit - Builtin exit function
 */
int	ft_exit(char **token)
{
	if (token[1] && invalid_exit_arg(token[1]))
	{
		// execute exit
		ft_putstr_fd("exit\n", 1);
		error_message_exit(EXIT_BAD_ARG, token[1]);
		return (2);
	}
	if (token[1] && token[2])
	{
		ft_putstr_fd("exit\n", 1);
		error_message_exit(EXIT_MANY_ARGS, NULL);
		return (1);
	}
	else
	{
		// execute exit
		ft_putstr_fd("exit\n", 1);
		if (token[1])
			return (ft_atoi(token[1]) % 256);
		else
		// gets the last exit code from previous process, not always 0
			return (0);
	}
}
/*
#include <string.h>

int	main()
{
	char	**token = NULL;
	int		exit_code = 0;

	token = malloc(3 * sizeof(char *));
	token[0] = "exit";
	token[1] = "-457407524";
	token[2] = "aa";
	if (strcmp(token[0], "exit") == 0)
		exit_code = ft_exit(token);
	return (exit_code);
}*/
