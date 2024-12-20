#include "./includes/ms.h"

int	arguments_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

bool	valid_builtin_args(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (false);
	return (true);
}
