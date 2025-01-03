#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;
/*
typedef struct	s_cmd
{
	char	*command;
	char	**args;
	int		infile;
	int		outfile_t;
	int		outfile_a;
	int		heredoc;
	int		tmp_doc[2];
	char	*eof;
}	t_cmd;
*/
typedef enum e_type
{
	WORD,
	PIPE,
	REDIN,
	REDOUT_T,
	REDOUT_A,
	HEREDOC,
	ENVMT,
	CMD,
}	t_type;

typedef enum e_quote_state
{
    NONE,
    SINGLE,
    DOUBLE
}	t_quote_state;

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
  struct  s_tree_node *left;
  struct  s_tree_node *right;
} t_tree_node;

typedef struct  s_data
{
	t_env	*env;
//	t_cmd	*cmd;
	t_tree_node	*tree;
    char    *prompt;
	char	*cwd;
	char	*input_user;
	char	**envp;
	char	**envp_path;
	int		total_cmds;
	int		total_process;
	int		*pid;
	int		*fd;  //array of fd for pipes
	int		exit_code;
}   t_data;

#endif
