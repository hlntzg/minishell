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
	   ./generate_ast_diagram.c \

HEADER = -I minishell.h

LIBFT_DIR = ./libft
LIBFT_FLAGS = -L $(LIBFT) -lft

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -r

all: createlibft $(NAME)

createlibft:
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME) 
	@echo "Compiling executable..."

clean:
	rm -f $(OBJS)
	rm -f $(LIBFT_DIR)/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)/libft.a

re:     fclean all

.PHONY: all clean fclean re

