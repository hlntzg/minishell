#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

char	**ft_split(char *str);
char	*get_file_path(char *file_name);
char	*get_file_loc(char *path, char *file_name);
int	startsWithForwardSlash(const char *str);

#endif
