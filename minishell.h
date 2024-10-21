/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:51:44 by hutzig            #+#    #+#             */
/*   Updated: 2024/10/21 15:23:40 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "lib/libft/libft.h"
#include <stdio.h>		/* readline */
#include <readline/readline.h>	/* readline */
#include <readline/history.h>	/* readline */
#include <signal.h>		/* signals */
#include <termios.h>		/* terminal attributs */

typedef struct s_data
{
	char	*prompt;
}	t_data;

void	set_signals(void);

#endif
