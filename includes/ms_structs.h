#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef	struct s_word
{
	char *some;
} 	t_word;


typedef struct	s_cmd
{
	char	*command;
	char	**args;

	int		word_count;
}	t_cmd;

typedef struct  s_data
{
	t_env	*env;
    char    *prompt;
	char	*cwd;
	char	*input_user;
	char	**envp;
	int		total_cmds;
	t_cmd	*cmd;
}   t_data;

#endif
