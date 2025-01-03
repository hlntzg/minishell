#include "./includes/ms.h"

int	count_cmd_args(char **_cmd)
{
	int	i;

	i = 0;
	while (_cmd[i])
		i++;
	return (i);
}

bool	valid_builtin_args(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (false);
	return (true);
}
