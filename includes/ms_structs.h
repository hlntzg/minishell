#ifndef MS_STRUCTS_H
# define MS_STRUCTS_H

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
    char    *prompt;
	char	*cwd;
	char	*input_user;
}   t_data;

#endif
