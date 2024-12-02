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

#include <stdio.h>		/* readline */
#include <readline/readline.h>	/* readline */
#include <readline/history.h>	/* readline */
#include <signal.h>		/* signals */
#include <termios.h>		/* terminal attributs */

typedef enum input_type {
	WORD = 1,
	PIPE = 2,
	REDIN = 3,
	REDOUT = 4,
	APPEND = 5,
	HEREDOC = 6,
	ENVMT = 7,
	BUILTIN = 8
}	token_type;

typedef struct s_data
{
	char	*prompt;
}	t_data;

typedef struct s_tok
{
	token_type input;
	void	*content;
	t_tok	*next;
}	t_tok;


//void	set_signals(void);

#endif
