/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:50:20 by hutzig            #+#    #+#             */
/*   Updated: 2025/02/14 09:46:53 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINES_H
# define MS_DEFINES_H

/**
 * MINISHELL - Error codes
 * 126: Command cannot be executed (it is not executable or missing permission)
 * 127: Command not found (does not exit in the PATH or wrong name)
 * -1: Execve fails to execute command
 */
# define ERR_NOT_EXEC 126
# define ERR_NOT_FOUND 127
# define ERR_EXECVE -1

# define ERR_SYNTAX "Syntax error: "
# define ERR_PIPE_OR_AMPERSAND "unexpected pipe or ampersand at the beginning"
# define ERR_QUOTES "unclosed quotes"
# define ERR_REDIR "invalid redirection"
# define ERR_OPERATOR "misplaced operator"
# define ERR_LOGICAL_OPERATORS "logical operators '&&' and '||' not supported"

# define ERR_AMBIGUOUS_REDIR "minishell: ambiguous redirect"

# define ERR_CD_OPTIONS "minishell: cd: no options available"
# define ERR_CD_ARGS "minishell: cd: too many arguments"
# define ERR_CD_NOHOME "minishell: cd: HOME not set"

# define ERR_PWD_OPTIONS "minishell: pwd: no options available"

# define ERR_EXP_OPTIONS "minishell: export: no options available"
# define ERR_EXP_BAD_KEY "minishell: export: not a valid identifier"

# define ERR_UNSET_OPTIONS "minishell: unset: no options available"

# define ERR_ENV_ARGS "minishell: env: too many arguments"
# define ERR_ENV_OPTIONS "minishell: env: no options available"

# define ERR_EXIT_ARGS "minishell: exit: too many arguments"
# define ERR_EXIT_BAD_ARG "minishell: exit: numeric argument required"

# define ERR_CMD_NOT_FOUND ": command not found"
# define ERR_FILE_ARG_REQUIRED ": filename argument required"

# define ERR_PERMISSION ": Permission denied"
# define ERR_IS_DIR ": Is a directory"
# define ERR_NO_FILE_OR_DIR ": No such file or directory"
# define ERR_NOT_DIR ": Not a directory"

# define ERR_PROCESS_PIPE "pipe error: "
# define ERR_PROCESS_FORK "fork failed: "
# define ERR_PROCESS_DUP2 "dup2 failed: "
# define ERR_PROCESS_CLOSE "close failed: "
# define ERR_PROCESS_OPEN "open failed: "
# define ERR_PROCESS_EXECVE "execve failed: "

# define ERR_MALLOC_FAIL "malloc failed: "

#endif
