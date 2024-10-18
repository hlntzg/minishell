#include "main.h"

char	*get_file_loc(char *path, char *file_name)
{
	char	*path_copy;
	char	*token;
	char	*path_buffer = NULL;
	struct stat file_path;		// variable used by stat()

	path_copy = strdup(path);	// so that we don't loose the original PATH when manipulating it
	token = strtok(path_copy, ":");
	while (token)
	{
		if (path_buffer)
		{
			free(path_buffer);
			path_buffer = NULL;
		}
		path_buffer = malloc(strlen(token) + strlen(file_name) + 2);	// +2 for "/" and '\0'
		if (!path_buffer)
		{
			perror("Error: malloc failed");
			exit(EXIT_FAILURE);
		}
	 	strcpy(path_buffer, token);
		strcat(path_buffer, "/");
		strcat(path_buffer, file_name);
		strcat(path_buffer, "\0");
		if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
		{
			free(path_copy);
			return (path_buffer);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	if (path_buffer)
		free(path_buffer);
	return (NULL);
}

char	*get_file_path(char *file_name)
{
	char	*path = getenv("PATH");
	char	*full_path;

	if (!path)
	{
		perror("Path not found");
		return (NULL);
	}
	full_path = get_file_loc(path, file_name);
	if (!full_path)
	{
		perror("Abosulte path not found");
		return (NULL);
	}
	return (full_path);
}
