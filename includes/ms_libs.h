/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_libs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:50:01 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/04 11:50:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LIBS_H
# define MS_LIBS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>		        /* readline */
# include <stdbool.h>
# include <errno.h>				/* errno */

# include <readline/readline.h>	/* readline */
# include <readline/history.h>	/* readline */

# include <sys/types.h>			/* waitpid */
# include <sys/wait.h>			/* waitpid */

# include <sys/stat.h>			/* open */
# include <fcntl.h>				/* open */

# include <signal.h>			/* signals */
# include <termios.h>			/* terminal attributes */

#endif
