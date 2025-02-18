/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:50:10 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/13 10:30:17 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H

# include "../libft/libft.h"
# include "./ms_structs.h"
# include "./ms_libs.h"
# include "./ms_defines.h"

/**
 * MINISHELL - Exit Status 
 * 0: success, as defined by the program 
 * 1: failure, as defined by the program
 * 2: command line usage error
 */
# define SUCCESS 0
# define FAILURE 1
# define ERR_CMD_LINE 2

# define READ 0
# define WRITE 1

extern int	g_sig;

/** main.c and ms_execute_newline.c
 * Functions related to the minishell workflow, from proccess the user
 * input to execution of the abstract syntax tree (AST).
 */
int			process_user_input(t_data *data, char *str, int *status);
int			ms_pre_exe_newline(t_data *data);
void		ms_exe_set_heredoc(t_data *data, t_tree_node *ast);
int			ms_execute_newline(t_data *data, int *status);
char		*get_abs_path(char *cmd, char **path);
int			ms_exe_command(t_data *data, char **_cmd, int *_pipe_fd);
int			ms_exe_builtin_cmd(t_data *data, char **_cmd, int *_pipe_fd);
int			ms_exe_external_cmd(t_data *data, char **_cmd, int *_pipe_fd);
int			ms_handle_pipe_execution(t_data *data, t_tree_node *ast,
				int *_pipe_fd);
int			ms_handle_redirection_execution(t_data *data,
				t_tree_node *ast, int *_pipe_fd);
int			ms_open_file(t_data *data, t_tree_node *ast, t_tree_node *prev);

/** ms_validity.c and ms_validity_utils.c
 *
 */
bool		no_lexical_errors(char *str);
bool		closed_quotes(char *str);
bool		valid_redirection(char *str);
bool		valid_pipes(char *str, int command);
bool		no_logical_operators(char *str);
void		quote_count(char *c, int *s_quote, int *d_quote);
int			is_redirection(char *c);

/** ms_lexing.c and ms_lexing_utils.c
 *
 */
t_token		*tokenizer(t_data *data, char *str);
t_token		*new_token(t_type type, char *content);
void		add_tokens(t_token **token, t_token *new);
char		*ft_strndup(char *src, int size);
void		free_tokens(t_token *token);

/** ms_parsing.c and ms_parsing_utils.c
 *
 */
t_tree_node	*parse_tokens(t_token **tokens);
t_tree_node	*create_redirection(t_token **tokens, t_token *temp);
t_tree_node	*new_tree_node(t_type type);
t_tree_node	*parse_redirection(t_token **tokens);
t_tree_node	*create_file_node(t_token *token);
int			argument_count(t_token *token);
int			has_space(const char *str);
int			count_expanded_args(t_token *tokens);
int			expand_count(char *content);
char		**split_expand(char **value, char *content, int *i);

/** ms_expansion.c and ms_expansion_utils.c
 *
 */
void		expand_variables(t_token **tokens, t_data *data);
char		*get_variable_value(t_env *env, char *var_name);
char		*get_variable_name(char *str, int start, int *length);
char		*ft_strjoin_char(char *str, char c);
char		*handle_exit_code(char *expanded, int exit_code, int *index);
void		free_null_node(t_token **tok, t_token **cur, t_token **prev);
char		*process_character(char *expanded, char c,
				int *s_quote, int *d_quote);

/** ms_env.c, ms_env_utils.c and ms_env_utils_lst.c 
 *
 */
void		set_environment(t_data *data, char **env);
char		*env_get_value(t_data *data, char *key);
int			env_get_key(t_data *data, char *key);
int			env_update_value(t_data *data, char *key, char *new_value);
t_env		*env_get_node(t_data *data, char *key);
char		**env_get_array_str(t_data *data);
char		**exe_get_path(char **envp);
t_env		*env_lstnew(char *key, char *value);
t_env		*env_lstlast(t_env *lst);
void		env_lstadd_back(t_env **lst, t_env *new);
void		env_add_new(t_data *data, char *key, char *value);
int			env_lstsize(t_env *lst);

/** ms_heredoc.c
 *
 */
int			ms_handle_heredoc(t_data *data, char *delimiter);
char		*expand_token_content(char *content, t_data *data, int *flag);
int			ms_heredoc(t_data *data, t_tree_node *ast, char *delimiter);
void		ms_exe_heredoc(t_data *data, int _out, char *eof, int expansion);
int			quoted_eof(char *delimiter);
char		*update_eof(char *delimiter);

/** ms_builtins.c, ms_builtins_print.c and builtins files
 *
 */
int			builtins(char *cmd);
int			ms_builtin_execution(t_data *data, char **_cmd, int *_out);
int			ms_exe_builtin_cmd(t_data *data, char **args, int *_pipe_fd);
int			ms_cd(t_data *data, char **_cmd);
int			ms_echo(t_data *data, char **_cmd, int *_out);
int			ms_env(t_data *data, char **_cmd, int *_out);
int			ms_exit(t_data *data, char **_cmd);
int			ms_export(t_data *data, char **_cmd, int *_out);
int			ms_pwd(t_data *data, char **_cmd, int *_out);
int			ms_unset(t_data *data, char **_cmd);
char		*ms_getpwd(t_data *data);
int			count_cmd_args(char **_cmd);
bool		valid_builtin_args(char *arg);
void		builtins_print_env_variables(t_data *data, int fd);
void		builtins_print_export_variables(t_data *data, int fd);

/** ms_exe_fds_utils.c
 *
 */
void		close_free_and_exit_child(t_data *data, int *_pipe_fd, int *_fd);
void		close_heredoc_fds(t_tree_node *ast);
void		close_fds(int read, int write);
int			std_save(t_data *data);
int			std_reset(t_data *data);

/** ms_signals.c and ms_signals_utils.c
 * 
 */
void		set_signals(void);
void		heredoc_signal(void);
void		quit_heredoc(t_data *signal);
void		set_heredoc_signal(int signum);
void		handle_sigint(int sig);
void		ignore_signals(void);
void		child_signal(void);
void		handle_sigquit(int signum);
void		handle_sigint_exe(int signum);
void		heredoc_sigint_exe(int signum);
void		restore_main_signals(void);

/** ms_error.c
  *
  */
int			ms_error(char *str, char *msg, int err_code, int return_code);
int			ft_error(char *str);

/** ms_free.c
 *
 */
void		update_minishell(t_data *data, int status);
void		free_and_exit_minishell(t_data *data, int status);
void		ms_free_and_exit_child(t_data *data, int status);
void		free_array(char **array);

/** ms_free_utils.c
 *
 */
void		free_char_double_ptr(char ***ptr);
void		free_env(t_data *data);
void		free_prompt(t_data *data);
void		free_pid(t_data *data);
void		free_ast(t_tree_node *ast);

#endif
