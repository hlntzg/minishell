#include <stdlib.h>	// malloc
#include <string.h> // strncpy ---> work on a ft_strncpy <-----------
typedef struct s_env
{
	char	**og_envp;
	char	***ms_envp;	// a 2D array where each environment variable is split into a key-value pair.
}	t_env;

//libft
int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

//libft 
char	*ft_strdup(const char *s1)
{
	char	*str_copy;
	int		i;

	str_copy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str_copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_copy[i] = s1[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}

//libft
char	*ft_strchr(const char *s, int c)
{
	char	convert_c;

	convert_c = (char) c;
	while (*s != '\0' || *s == '\0')
	{
		if (*s == convert_c)
			return ((char *) s);
		else if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}

//libft
int	ft_strequ(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}

//libft
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




static char	**duplicate_system_environment(char **og_envp)
{
	int		i;
	int		j;
	char	**env_copy;

	i = 0;
	while (og_envp[i])
		i++;
	env_copy = malloc(sizeof(char **) * (i + 1));
	if (!env_copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		env_copy[j] = ft_strdup(og_envp[j]);
		j++;
	}
	env_copy[j] = NULL;
	return (env_copy);
}

static int	initialize_env_data(char **og_envp, t_env *env)
{
	int	i;
	int	j;
	int	k;

	env->og_envp = duplicate_system_environment(og_envp);
	if (!env->og_envp)
		return (0);
	i = 0;
	while (og_envp[i])
		i++;
	env->ms_envp = malloc(sizeof(char ***) * (i + 1));
	if (!env->ms_envp)
		return (0);
	j = 0;
	while (j < i)
	{
		k = ft_strchr(og_envp[j], '=') - og_envp[j];
		env->ms_envp[j] = malloc(sizeof(char **) * 2);
		env->ms_envp[j][0] = malloc(sizeof(char *) * k + 1);
		env->ms_envp[j][1] = malloc(sizeof(char *) * (ft_strlen(og_envp[j]) - k));
		if (!env->ms_envp || !env->ms_envp[j][0] || !env->ms_envp[j][1])
			return (0);
		strncpy(env->ms_envp[j][0], og_envp[j], k);
		env->ms_envp[j][0][k] = '\0';
		strncpy(env->ms_envp[j][1], &og_envp[j][k + 1], ft_strlen(og_envp[j]) - k - 1);
		env->ms_envp[j][1][ft_strlen(og_envp[j]) - k - 1] = '\0';
		j++;
	}
	env->ms_envp[j] = NULL;
	return (1);
}

int	get_env_var_index(char *var, t_env *env)
{
	int	i;
	
	i = 0;
	while (env->ms_envp[i])
	{
		if (ft_strequ(var, env->ms_envp[i][0]))
			return (i);
		i++;
	}
	return (-1);
}

#include <stdio.h>
void	manage_env_var(t_env *env, char *var)
{
	int		index;
	int		k;
	char	*var_name;

	k = ft_strchr(var, '=') - var;
	var_name = malloc(sizeof(char) * (k + 1));
	if (!var_name)
		return ;
	strncpy(var_name, var, k);
	var_name[k] = '\0';
	index = get_env_var_index(var_name, env);
	if (index >= 0)
		printf("\nremoving value ... SHELL=minishell\n");
		//remove_env_var_value();
	free(var_name);
	if (k > 0 && k < ft_strlen(var))	// Case: "NEW_VAR=something"
		printf("\nupdate value ... SHELL=minishell\n");
		//add_env_var_entry();
	else if (var[k] == '=')				// Case: "NEW_VAR="
		printf("\ncase NEW_VAR=\n");
		//add_env_var_entry();
	else if (k == ft_strlen(var))		// Case: "NEW_VAR"
		printf("\ncase NEW_VAR\n");
		//add_env_var_entry();
}

void	set_up_env_variables(t_env *env)
{
	//char	*pwd;

	manage_env_var(env, "SHELL=minishell");
}

int	initialize_shell_env(char **og_envp, t_env *env)
{
	int	env_status;
	int	var_index;

	if (!env)
		return (0);
	env_status = initialize_env_data(og_envp, env);
	var_index = get_env_var_index("SHLVL", env);
	if (var_index < 0)
		var_index = 0;
	else
		var_index = ft_atoi(env->ms_envp[var_index][1]);
	// set_shell_level // NOTE: need to work on this function
	set_up_env_variables(env);
	return (env_status);
}


#include <stdio.h>
int	main(int argc, char **argv, char **og_envp)
{
	t_env	*env;

	(void) argv;
	if (argc != 1)
	{
		printf("minishell: exit: too many arguments"); //should be in stderr
		exit (127);
	}
	env = malloc(sizeof(t_env));
	if (initialize_shell_env(og_envp, env))
	{
		printf("OK FOR MAIN SHELL LOOP\n\n");
		int i = 0;
		while (env->ms_envp[i] && env->og_envp)
		{
			printf("original:\t%s\n", env->og_envp[i]);
			printf("variable:\t%s\t\t\tvalue: %s\n", env->ms_envp[i][0], env->ms_envp[i][1]);
			i++;
		}
	}
	else
		printf("error in initializing env");
}
