#ifndef MS_H
# define MS_H

# include "../libft/libft.h"
# include "./ms_structs.h"
# include "./ms_libs.h"
# include "./ms_defines.h"

# define SUCCESS 0

void	set_environment(t_data *data, char **env);
char	*env_get_value(t_data *data, char  *key);
int		env_get_key(t_data *data, char *key);
int	env_update_value(t_data *data, char *key, char *new_value);

t_env	*env_lstnew(char *key, char *value);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_add_new(t_data *data, char *key, char *value);
int	env_lstsize(t_env *lst);

void	builtins_print_env_variables(t_data *data, int fd);
void	builtins_print_export_variables(t_data *data, int fd);

char	**env_get_array_str(t_data *data);
char	**exe_get_path(char **envp);


void	ms_execute_newline(t_data *data);

int		ms_echo(t_data *data, t_cmd *cmd);
int		ms_env(t_data *data, t_cmd *cmd);
int		ms_exit(t_data *data, t_cmd *cmd);
int		ms_export(t_data  *data, t_cmd *cmd);
int		ms_pwd(t_data *data, t_cmd *cmd);

int	arguments_count(char **args);
bool	valid_builtin_args(char *str);

#endif
