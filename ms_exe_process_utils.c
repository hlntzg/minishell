/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exe_process_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:42:50 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/11 15:33:19 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ms.h"
#include <sys/stat.h>

char	*get_path(char *cmd, char **path, struct stat path_stat, int len_cmd)
{
	int			len_path;
	char		*pathname;

	while (*path)
	{
		len_path = ft_strlen(*path);
		pathname = malloc(len_cmd + len_path + 2);
		if (!pathname)
			return (NULL);
		ft_strcpy(pathname, *path);
		if (pathname[len_path - 1] != '/')
		{
			pathname[len_path] = '/';
			pathname[len_path + 1] = '\0';
		}
		ft_strlcat(pathname, cmd, len_cmd + len_path + 2);
		if (stat(pathname, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		{
			if (access(pathname, X_OK) == 0)
				return (pathname);
		}
		free(pathname);
		path++;
	}
	return (NULL);
}

char	*get_abs_path(char *cmd, char **path)
{
	char		*pathname;
	struct stat	path_stat;
	int			len_cmd;

	len_cmd = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~' || ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
				return (cmd);
			else if (access(cmd, X_OK) == 0)
				return (cmd);
			else
				errno = EACCES;
		}
		return (NULL);
	}
	if (stat(cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (cmd);
	pathname = get_path(cmd, path, path_stat, len_cmd);
	return (pathname);
}
