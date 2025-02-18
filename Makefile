# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 10:08:00 by nmeintje          #+#    #+#              #
#    Updated: 2025/02/13 09:46:58 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	main.c \
		ms_lexing.c \
		ms_lexing_utils.c \
		ms_validity.c \
		ms_validity_utils.c \
		ms_parsing.c \
		ms_parsing_utils.c \
		ms_builtin_cd.c \
		ms_builtin_echo.c \
		ms_builtin_env.c \
		ms_builtin_exit.c \
		ms_builtin_export.c \
		ms_builtin_pwd.c \
		ms_builtins_print.c \
		ms_builtin_unset.c \
		ms_env.c \
		ms_env_utils.c \
		ms_env_utils_lst.c \
		ms_exe_process_utils.c \
		ms_pre_exe_newline.c \
		ms_error.c \
		ms_builtins.c \
		ms_process_user_input.c \
		ms_expansion.c \
		ms_expansion_utils.c \
		ms_signals.c \
		ms_signals_utils.c \
		ms_exe_builtin_cmd.c \
		ms_exe_external_cmd.c \
		ms_exe_pipe_and_redirection.c \
		ms_execute_newline.c \
		ms_exe_heredoc.c \
		ms_free.c  \
		ms_free_utils.c \
		ms_utils.c \
		ms_exe_fds_utils.c \
		ms_env_get.c \
		ms_exe_open_and_handle_files.c \

HEADER = ./includes/ms.h

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT)

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: createlibft $(NAME)

createlibft:
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline $(LIBFT_FLAGS) -o $(NAME) 
	@echo "Compiling executable..."

clean:
	rm -f $(OBJS)
	rm -f $(LIBFT_DIR)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/libft.a

re:     fclean all

.PHONY: all clean fclean re
