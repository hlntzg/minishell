#include "./includes/ms.h"

void	set_environment(t_data *data, char **env)
{
	(void)data;
	int	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
