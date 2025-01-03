/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:53:06 by nmeintje          #+#    #+#             */
/*   Updated: 2024/11/29 10:53:15 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>		/* readline */
# include <readline/readline.h>	/* readline */
# include <readline/history.h>	/* readline */
# include <signal.h>		/* signals */
# include <termios.h>		/* terminal attributes */
# include <stdbool.h>	/* boolean functions */
# include <stdlib.h>	/* malloc */
# include "./libft/libft.h"
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1
# define ERR_CMD_LINE 2
# define ERR_PROCESS_FORK "fork failed: "

typedef enum e_type {
	WORD,
	PIPE,
	REDIN,
	REDOUT_T,
	REDOUT_A,
	HEREDOC,
	ENVMT,
	CMD,
}	t_type;

typedef enum e_quote_state {
    NONE,
    SINGLE,
    DOUBLE
}	t_quote_state;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct  s_data
{
	t_env	*env;
	//t_cmd	*cmd;
    char    *prompt;
	char	*cwd;
	char	*input_user;
	char	**envp;
	char	**envp_path;
	int		total_cmds;
	int		total_process;
	int		*pid;
	int		*fd;  //array of fd for pipes
}   t_data;

typedef struct s_token
{
	t_type type;
	char	*content;
	struct s_token	*next;
}	t_token;

typedef struct s_tree_node
{
  t_type  type;
  char        **value;
  int		infile;
  int		outfile_t;
  int		outfile_a;
  int		heredoc;
  int		tmp_doc[2];
  struct  s_tree_node *left;
  struct  s_tree_node *right;
} t_tree_node;

typedef struct	s_cmd
{
	char	*command;
	char	**args;
	int		infile;
	int		outfile_t;
	int		outfile_a;
	int		heredoc;
	int		tmp_doc[2];
}	t_cmd;

//void	set_signals(void);

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

//validity
bool	no_lexical_errors(char *str);
void	quote_count(char *c, int *s_quote, int *d_quote);
int		is_redirection(char *c);

// expansion
void	set_environment(t_data *data, char **env);
t_env	*env_lstnew(char *key, char *value);
t_env	*env_lstlast(t_env *lst);
void	env_lstadd_back(t_env **lst, t_env *new);
void	env_add_new(t_data *data, char *key, char *value);
int		env_lstsize(t_env *lst);
void	builtins_print_env_variables(t_data *data, int fd);
void	builtins_print_export_variables(t_data *data, int fd);
char	**env_get_array_str(t_data *data);
char	**exe_get_path(char **envp);
char	*env_get_value(t_data *data, char  *key);

// free and exit
void	free_tree(t_tree_node *node);
int		ft_error(char *str);

//echo 
int	ms_echo(t_data *data, t_tree_node *node);

//execution
int execute_newline(t_data *data, t_tree_node *node);
int execute_builtin(t_data *data, t_tree_node *node);

// testing
void print_tokens(t_token *token);
void test_tokenizer(void);
void test_parser(void);
void print_ast(t_tree_node *node, int depth);

#endif
