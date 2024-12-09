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
# include "libft/libft.h"


typedef enum e_type {
	ARG,
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC,
	ENVMT,
	CMD,
}	t_type;

typedef struct s_data
{
	char	*prompt;
}	t_data;

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
  int         index;
  struct  tree_node *left;
  struct  tree_node *right;
} t_tree_node;

typedef struct s_env
{
  char  *key;
  char  *value;
} t_env;

//void	set_signals(void);

// lexical analysis
t_token	*new_token(t_type type, char *content);
void	add_tokens(t_token **token, t_token *new);

//validity
bool	lexical_errors(char *str);
void	quote_count(char *c, int *s_quote, int *d_quote);
int		is_redirection(char *c);

#endif
