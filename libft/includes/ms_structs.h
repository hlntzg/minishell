#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

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

typedef struct  s_data
{
	t_env	*env;
	t_cmd	*cmd;
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

#endif
