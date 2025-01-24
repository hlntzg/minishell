/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:53:06 by nmeintje          #+#    #+#             */
/*   Updated: 2025/01/03 16:10:31 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./includes/ms.h"

extern int	g_sig;

int     process_user_input(t_data *data, char *str);

// signals
void	set_signals(void);
void	heredoc_signal(void);
void	quit_heredoc(t_data *signal);
void	set_heredoc_signal(int signum);
void	handle_sigint(int sig);
void	ignore_signals(void);
void	child_signal(void);
void	handle_sigquit(int signum);
void	handle_sigint_exe(int signum);

// lexing
t_token *tokenizer(char *str);
t_token	*new_token(t_type type, char *content);
void	add_tokens(t_token **token, t_token *new);
char	*ft_strndup(char *src, int size);
void 	free_tokens(t_token *token);

// parsing
t_tree_node *parse_tokens(t_token **tokens);
t_tree_node	*create_redirection(t_token **tokens, t_token *temp);
t_tree_node	*new_tree_node(t_type type);
t_tree_node *parse_redirection(t_token **tokens);
t_tree_node *create_file_node(t_token *token);
int			argument_count(t_token *token);
void		free_ast(t_tree_node *node);

// expansion
void    expand_variables(t_token *tokens, t_env *env, int exit_code);
char    *get_variable_value(t_env *env, char *var_name);
char    *get_variable_name(char *str, int start, int *length);
char    *ft_strjoin_char(char *str, char c);
char    *handle_exit_code(char *expanded, int exit_code, int *index);

// heredoc
int     quoted_eof(char *delimiter);
char	*update_eof(char *delimiter);

//validity
bool	no_lexical_errors(char *str);
void	quote_count(char *c, int *s_quote, int *d_quote);
int		is_redirection(char *c);

// free and exit
void	free_tree(t_tree_node *node);
int		ft_error(char *str);

// free
void	free_char_double_ptr(char ***ptr);
void	ms_free(t_data *data);

// testing
void print_tokens(t_token *token);
void test_tokenizer(void);
void test_parser(void);
void print_ast(t_tree_node *node, int depth);

#endif
