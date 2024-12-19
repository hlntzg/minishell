# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/29 10:08:00 by nmeintje          #+#    #+#              #
#    Updated: 2024/11/29 10:08:45 by nmeintje         ###   ########.fr        #
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
	   ./expansion.c	\
	   ./generate_ast_diagram.c \
	   ./testing.c \

HEADER = minishell.h

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT)

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

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

