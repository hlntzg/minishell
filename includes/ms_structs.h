/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:50:51 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/14 10:04:51 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				expand;
	struct s_token	*next;
}	t_token;

typedef struct s_tree_node
{
	t_type				type;
	char				**value;
	int					expand;
	int					status;
	int					fd[2];
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_data
{
	t_env		*env;
	t_tree_node	*tree;
	char		*prompt;
	char		*cwd;
	char		*input_user;
	char		**envp;
	char		**envp_path;
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
	int			std[2];
	int			exit_code;
}	t_data;

#endif
