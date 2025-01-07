#ifndef MS_H
# define MS_H

# include "../libft/libft.h"
# include "./ms_structs.h"
# include "./ms_libs.h"
# include "./ms_defines.h"
# include "../minishell.h"

/**
 * MINISHELL - Exit Status 
 * 0: success, as defined by the program 
 * 1: failure, as defined by the program
 * 2: command line usage error
 */
# define SUCCESS 0
# define FAILURE 1
# define ERR_CMD_LINE 2

// error
int	ms_error(char *str, char *msg, int err_code, int return_code);

// env
void	set_environment(t_data *data, char **env);
char	*env_get_value(t_data *data, char  *key);
int		env_get_key(t_data *data, char *key);
int		env_update_value(t_data *data, char *key, char *new_value);
t_env   *env_get_node(t_data *data, char *key);
// env utils
char	**env_get_array_str(t_data *data);
char	**exe_get_path(char **envp);
// env utils lst
t_env	*env_lstnew(char *key, char *value);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_add_new(t_data *data, char *key, char *value);
int		env_lstsize(t_env *lst);

// execution
int		ms_execute_newline(t_data *data);
int		ms_pre_exe_newline(t_data *data);
int		ms_exe_pipeline(t_data *data);
int ms_exe_external_cmd(t_data *data, char **_cmd);

char	*get_abs_path(char *cmd, char **path);


// builtins
int	builtins(char *cmd);
int	ms_exe_builtin(t_data *data, char **args);
int		ms_cd(t_data *data, char **_cmd);
int		ms_echo(t_data *data, char **_cmd);
int		ms_env(t_data *data, char **_cmd);
int		ms_exit(t_data *data, char **_cmd);
int		ms_export(t_data  *data, char **_cmd);
int		ms_pwd(t_data *data, char **_cmd);
int		ms_unset(t_data *data, char **_cmd);
char    *ms_getpwd(t_data *data);
// builtins utils
int		count_cmd_args(char **_cmd);
bool	valid_builtin_args(char *arg);
// printing builtins
void	builtins_print_env_variables(t_data *data, int fd);
void	builtins_print_export_variables(t_data *data, int fd);



#endif
