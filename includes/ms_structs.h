#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef enum e_ast_status
{
	READY,
	EXECUTE_CMD,
	WRITE_TO_T,
	WRITE_TO_A,
	READ_FROM,
	READ_HEREDOC,
}	t_ast_status;

typedef enum e_type
{
	WORD,
	PIPE,
	REDIN,
	REDOUT_T,
	REDOUT_A,
	HEREDOC,
}	t_type;

typedef enum e_quote_state
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote_state;

typedef struct s_token
{
	t_type			type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_tree_node
{
	t_type				type;
	char				**value;
	int					status;
	int					fd[2];
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_data
{
	t_env		*env;/* free just when exit*/
	t_tree_node	*tree;
	char		*prompt;
	char		*cwd;
	char		*input_user;
	char		**envp; // always free?
	char		**envp_path; // always free?
	int			*pid;
	int			count_infile;
	int			count_outfile;
	int			count_pipe;
	int			count_heredoc;
	int			processes;
	int			count_child;
	int			redirect_input;
	int			redirect_output;
	int			heredoc;
	int			fd[2];
	int			exit_code; //dont reset inside while(1)
}	t_data;

#endif
