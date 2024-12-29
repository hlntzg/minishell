char	*get_abs_path(char *cmd, char **path)
{
	char	*pathname[PATH_MAX];
	int		len_cmd;
	int		len_path;
	
	if ((cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~') && access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		else
			return (NULL); // error "minishell: Permission denied: cmd" exit code ERR_NOT_EXEC (126)
	}
	while (*path)
	{
		len_cmd = ft_strlen(cmd);
		len_path = ft_strlen(*path);
        ft_strcpy(pathname, *path);
		if (pathname[len_path - 1] != '/')
		{
			pathname[len_path] == '/';
			pathname[len_path + 1] == '\0';
		}
		ft_strlcat(pathname, cmd, len_cmd + len_path + 2);
		if (access(pathname, X_OK) == 0) // Check if the path is executable
			return (pathname);
		path++;
	}
	ms_error(cmd, ERR_CMD_NOT_FOUND, ERR_NOT_FOUND, FAILURE);
	//ft_putendl_fd(ERR_CMD_NOT_FOUND, STDERR_FILENO); // exit code ERR_NOT_FOUND (127)
	return (NULL);
}

/**
 * invalid_cmd - Checks if a command argument is valid.
 * @cmd: The command string to check.
 *
 * This function verifies whether a given command string is valid. 
 * It checks for NULL or empty strings and ensures that at least one 
 * printable character exists that is not whitespace.
 *
 * Return: 1 if invalid; 0 if valid.
 */
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
}
