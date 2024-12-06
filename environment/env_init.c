#include <stdlib.h>	// malloc
//#include <string.h> // strncpy ---> work on a ft_strncpy <-----------
#include <unistd.h>
#include <stdio.h>
/**
 * s_env - Environment variable structure
 *
 * This structure holds environment variable information:
 * @og_envp: Copy of original environment variables array
 * @ms_envp: 2D array where each environment variable is split into a var-value pair.
 */
typedef struct s_env
{
	char	**og_envp;
	char	***ms_envp;
}	t_env;


////////////////////////////////////////
//libft
int	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
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
//libft 
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
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

//libft itoa
static int	len_n(int long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			len;
	int long	nb;

	nb = n;
	len = len_n(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	i = len;
	while (nb != 0 && i-- > 0)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
	}
	str[len] = '\0';
	return (str);
}

//libft new ******************************
char    *ft_strcpy(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s2[i])
    {
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

//libft 
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}

//libft new ******************************
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

//libft new ******************************
//libft new ft_strncpy
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i]) 
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/////////////////////////////////////////////////////////


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
		ft_strncpy(env->ms_envp[j][0], og_envp[j], k);
		env->ms_envp[j][0][k] = '\0';
		ft_strncpy(env->ms_envp[j][1], &og_envp[j][k + 1], ft_strlen(og_envp[j]) - k - 1);
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

void	remove_env_var_value(t_env *env, char *var, int index)
{
	(void) var;
	if (env->ms_envp[index][1])
		free(env->ms_envp[index][1]);
}

void	add_env_var_value(t_env *env, char *var, int k, int index)
{
	int	j;

	if (index >= 0) //existing variable 
	{
		j = ft_strlen(var) - (k + 1);
		env->ms_envp[index][1] = malloc(sizeof(char) * (j + 1));
		if (!env->ms_envp[index][1])
			return ;
		ft_strncpy(env->ms_envp[index][1], &var[k + 1], j);
		env->ms_envp[index][1][j] = '\0';
	}
	else
		printf("new variable for adding on envp");
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
	ft_strncpy(var_name, var, k);
	var_name[k] = '\0';
	index = get_env_var_index(var_name, env);
	free(var_name);
	if (k > 0 && k < ft_strlen(var) && index >= 0)	// Case: "OLD_VAR=newsomething"
	{
		remove_env_var_value(env, var, index);
		add_env_var_value(env, var, k, index);
	}
	else if (var[k] == '=')				// Case: "NEW_VAR="
		printf("\ncase NEW_VAR=\n");
		//add_env_var_entry(env, var, i);
	else if (k > 0 && k < ft_strlen(var) && index == -1)	// Case: "NEW_VAR=something"
		printf("\ncase NEW_VAR=somenthing\n");
	else if (k == ft_strlen(var))		// Case: "NEW_VAR"
		printf("\ncase NEW_VAR\n");
		//add_env_var_entry(env, var, i);
}

void	set_up_env_variables(t_env *env)
{
	//char	*pwd;
	manage_env_var(env, "SHELL=minishell");
}

void	update_env_value(t_env *env, char *var, int value)
{
	char	*update_value;
	int		j;

	if (!env || !var)
		return ;
	update_value = ft_itoa(value);
	if (!update_value)
		return ;
	j = get_env_var_index(var, env);
	if (j < 0)
	{
		free(update_value);
		return ;
	}
	if (env->ms_envp[j][1])
		free(env->ms_envp[j][1]);
	env->ms_envp[j][1] = malloc(sizeof(char *) * (ft_strlen(update_value) + 1));
	if (!env->ms_envp[j][1])
	{
		free(update_value);
		return ;
	}
	ft_strcpy(env->ms_envp[j][1], update_value);
	free(update_value);
}

char	**set_shell_basic_env_var(void)
{
	char	*cwd;
	char	**env;

	cwd = getcwd(NULL, 0);
	cwd = ft_strjoin("PWD=", cwd);
	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strdup(cwd);
	env[1] = ft_strdup("SHLVL=2");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	free(cwd);
	return (env);
}

int	initialize_shell_env(char **og_envp, t_env *env)
{
	int		status;
	int		index;

	if (!env)
		return (0);
	if (!og_envp || !og_envp[0])
		og_envp = set_shell_basic_env_var();
	status = initialize_env_data(og_envp, env);
	index = get_env_var_index("SHLVL", env);
	if (index < 0)
		index = 0;
	else
		index = ft_atoi(env->ms_envp[index][1]);
	update_env_value(env, "SHLVL", index + 1); // setting correct shell level
	set_up_env_variables(env);
	return (status);
}

//env.c
static void	print_env_var(char *var, char *value, int fd)
{
	ft_putstr_fd(var, fd);
	ft_putstr_fd("=", fd);
	if (value)
		ft_putstr_fd(value, fd);
	ft_putstr_fd("\n", fd);
}

int	ft_env(char **token, t_env *env, int fd)
{
	(void)token;
	int	i;

	i = 0;
	while (env->ms_envp[i])
	{
		print_env_var(env->ms_envp[i][0], env->ms_envp[i][1], fd);
		i++;
	}
	return (0);
}

//pwd.c
int	ft_pwd(char **token, t_env *env, int fd)
{
	(void)token;
	char	*cwd;
	int		i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		while (env && env->ms_envp[i])
		{
			if (env->ms_envp[i][0] && ft_strequ("PWD", env->ms_envp[i][0]))
			{
				cwd = env->ms_envp[i][1];
				break ;
			}
			i++;
		}
		if (!cwd)
			return (-1); // error if getcwd fails or no PWD on env
	}
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	if (cwd != env->ms_envp[i][1])
		free(cwd);
	return (0);
}

char	***duplicate_ms_environment(t_env *env)
{
	int		i;
	int		j;
	char	***copy_ms_envp;

	i = 0;
	while (env->ms_envp[i])
		i++;
	copy_ms_envp = malloc(sizeof(char ***) * (i + 1));
	if (!copy_ms_envp)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy_ms_envp[j] = malloc(sizeof(char **) * 2);
		copy_ms_envp[j][0] = ft_strdup(env->ms_envp[j][0]);
		copy_ms_envp[j][1] = ft_strdup(env->ms_envp[j][1]);
		if (!copy_ms_envp[j] || !copy_ms_envp[j][0] || !copy_ms_envp[j][1])
			return (NULL);
		j++;
	}
	copy_ms_envp[j] = NULL;
	return (copy_ms_envp);
}

void	bubble_sort_env(char ***ms_envp)
{
	int	i;
	int	j;
	int	k;
	char	**tmp;

	i = 0;
	j = 0;
	while (ms_envp[i])
		i++;
	while (j < i - 1)
	{
		k = 0;
		while (k < i - j - 1)
		{
			if (ft_strcmp(ms_envp[k][0], ms_envp[k + 1][0]) > 0)
			{
				tmp = ms_envp[k];
				ms_envp[k] = ms_envp[k + 1];
				ms_envp[k + 1] = tmp;
			}
			k++;
		}
		j++;
	}
}

void	print_export_var(t_env *env, int fd)
{
	char	***tmp_ms_envp;
	int		i;

	tmp_ms_envp = duplicate_ms_environment(env);
	bubble_sort_env(tmp_ms_envp);
	i = 0;
	while (tmp_ms_envp[i])
	{
		if (ft_strequ("_", tmp_ms_envp[i][0]))
			break ;
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp_ms_envp[i][0], fd);
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		if (tmp_ms_envp[i][1][0])
			ft_putstr_fd(tmp_ms_envp[i][1], fd);
		ft_putchar_fd('"', fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}

//export.c
int	ft_export(char **token, t_env *env, int fd)
{
	(void)token;
	//if no extra thing after 'export'
	print_export_var(env, fd);
	return (0);
}


#include <stdio.h>
int	main(int argc, char **argv, char **og_envp)
{
	t_env	*env;

	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit (127);
	}
	env = malloc(sizeof(t_env));
	if (initialize_shell_env(og_envp, env))
	{
	//	printf("OK FOR MAIN SHELL LOOP\n\n");
		ft_env(NULL, env, 2);
	//	ft_pwd(NULL, env, 1);
	//	ft_export(NULL, env, 2);
	/*	int i = 0;
		while (env->ms_envp[i] && env->og_envp)
		{
			printf("original:\t%s\n", env->og_envp[i]);
			printf("variable:\t%s\t\t\tvalue: %s\n", env->ms_envp[i][0], env->ms_envp[i][1]);
			i++;
		}*/
	}
	else
		printf("error in initializing env");
}
