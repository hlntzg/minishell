#include "./includes/ms.h"
#include <sys/stat.h>

char	*get_abs_path(char *cmd, char **path)
{
	char	*pathname;
	int		len_cmd;
	int		len_path;
	struct stat path_stat;

	// Case 1: Absolute or relative path is provided (e.g., "./script.sh", "/usr/bin/ls")
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~' || ft_strchr(cmd, '/'))
	{
		printf("get_abs_path:  [1]\n");
		if (stat(cmd, &path_stat) == 0) // Check if the path exists
		{
			if (S_ISDIR(path_stat.st_mode)) // Directory case
				return ft_strdup(cmd);
			else if (access(cmd, X_OK) == 0) // File and executable case
				return ft_strdup(cmd);
			else
				errno = EACCES;
		}
		return (NULL);
		//return (ft_strdup(cmd)); // Invalid path
	}
// Case 3: Handle if it's a directory found in the current directory
	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		printf("get_abs_path:  [2]\n");
		return ft_strdup(cmd);
	}
	while (*path) // Case 2: Search in PATH for executables
	{
		printf("get_abs_path:  [3]\n");
		len_cmd = ft_strlen(cmd);
		len_path = ft_strlen(*path);
		pathname = malloc(len_cmd + len_path + 2);
		if (!pathname)
			return (NULL); // Handle malloc failure
		ft_strcpy(pathname, *path);
		if (pathname[len_path - 1] != '/')
		{
			pathname[len_path] = '/';
			pathname[len_path + 1] = '\0';
		}
		ft_strlcat(pathname, cmd, len_cmd + len_path + 2);
		if (stat(pathname, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode)) // Not a directory
		{
			if (access(pathname, X_OK) == 0) // Check if it's executable
				return (pathname);
		}
		free(pathname);
		path++;
	}
	return (NULL);
}

/*
{
	char	*pathname;
	int		len_cmd;
	int		len_path;
	
	if ((cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~') && access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		else
		{
			ms_error(cmd, ERR_PERMISSION, ERR_NOT_EXEC, FAILURE); //exit code 126
			return (NULL); // error "minishell: Permission denied: cmd" exit code ERR_NOT_EXEC (126)
		}
	}
	while (*path)
	{
		len_cmd = ft_strlen(cmd);
		len_path = ft_strlen(*path);
        pathname = malloc(sizeof(char) * (len_cmd + len_path + 2));
		if (!pathname)
			return (NULL); //malloc error
		ft_strcpy(pathname, *path);
		if (pathname[len_path - 1] != '/')
		{
			pathname[len_path] = '/';
			pathname[len_path + 1] = '\0';
		}
		ft_strlcat(pathname, cmd, len_cmd + len_path + 2);
		if (access(pathname, X_OK) == 0) // Check if the path is executable
			return (pathname);
		free(pathname);
		path++;
	}
	ms_error(cmd, ERR_CMD_NOT_FOUND, ERR_NOT_FOUND, FAILURE); //exit code ERR_NOT_FOUND (127)
	return (NULL);
}*/


/*
**
 * invalid_cmd - Checks if a command argument is valid.
 * @cmd: The command string to check.
 *
 * This function verifies whether a given command string is valid. 
 * It checks for NULL or empty strings and ensures that at least one 
 * printable character exists that is not whitespace.
 *
 * Return: 1 if invalid; 0 if valid.
 *
int	invalid_cmd(char *cmd)
{
	int	i;

	if (!cmd || cmd[0] == '\0')
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (ft_isprint(cmd[i]) && !ft_iswhitespace(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}*/
