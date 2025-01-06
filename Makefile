# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 10:08:00 by nmeintje          #+#    #+#              #
#    Updated: 2025/01/03 16:07:52 by hutzig           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./main.c         \
       ./lexing.c         \
	   ./lexing_utils.c    \
	   ./validity.c  \
	   ./validity_utils.c  \
	   ./parsing.c	\
	   ./parsing_utils.c \
	   ./errors.c \
	   ms_builtin_cd.c \
	   ms_builtin_echo.c \
	   ms_builtin_env.c \
	   ms_builtin_exit.c \
	   ms_builtin_export.c \
	   ms_builtin_pwd.c \
	   ms_builtins_print.c \
	   ms_builtins_utils.c \
	   ms_builtin_unset.c \
	   ms_env.c \
	   ms_env_utils.c \
	   ms_env_utils_lst.c \
		ms_exe_process.c \
		process_user_input.c \
		expansion.c \

HEADER = ./includes/ms.h

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT)

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
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

