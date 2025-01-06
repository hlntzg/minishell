#ifndef MS_DEFINES_H
# define MS_DEFINES_H

# define ERR_CD_OPTIONS "minishell: cd: no options available"
# define ERR_CD_ARGS "minishell: cd: too many arguments"
# define ERR_CD_NOHOME "minishell: cd: HOME not set"

# define ERR_PWD_OPTIONS "minishell: pwd: no options available"

# define ERR_EXP_OPTIONS "minishell: export: no options available"
# define ERR_EXP_BAD_KEY "minishell: export: not a valid identifier"

# define ERR_UNSET_OPTIONS "minishell: unset: no options available"

# define ERR_ENV_ARGS "minishell: env: too many arguments" //arg or options - need to be update
# define ERR_ENV_OPTIONS "minishell: env: no options available" //arg or options - need to be update

# define ERR_EXIT_ARGS "minishell: exit: too many arguments"
# define ERR_EXIT_BAD_ARG "minishell: exit: numeric argument required"

/**
 * MINISHELL - Error codes
 * 126: Command cannot be executed (it is not executable or missing permission)
 * 127: Command not found (does not exit in the PATH or wrong name)
 * -1: Execve fails to execute command
 */
# define ERR_NOT_EXEC 126
# define ERR_NOT_FOUND 127
# define ERR_EXECVE -1

# define ERR_CMD_NOT_FOUND ": command not found"
# define ERR_FILE_ARG_REQUIRED ": filename argument required\n.: usage: . filename [arguments]"

# define ERR_PERMISSION ": Permission denied" //126
# define ERR_IS_DIR ": Is a directory" // 126
# define ERR_NO_FILE_OR_DIR ": No such file or directory"
# define ERR_NOT_DIR ": Not a directory"

# define ERR_PROCESS_PIPE "pipe error: "
# define ERR_PROCESS_FORK "fork failed: "
# define ERR_PROCESS_DUP2 "dup2 failed: "
# define ERR_PROCESS_CLOSE "close failed: "
# define ERR_PROCESS_EXECVE "execve failed: "

# define ERR_MALLOC_FAIL "malloc failed: "

#endif
