#ifndef MS_H
# define MS_H

#include "../libft/libft.h"
#include "./ms_structs.h"
#include "./ms_libs.h"

void	set_environment(t_data *data, char **env);

t_env	*env_lstnew(char *key, char *value);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_add_new(t_data *data, char *key, char *value);

void	builtins_print_env_variables(t_data *data, int fd);
void	builtins_print_export_variables(t_data *data, int fd);

#endif