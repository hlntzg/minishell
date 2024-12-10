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

NAME = philo

SRCS = ./main.c         \
       ./exit.c         \
           ./utils.c    \
           ./threads.c  \
           ./routine.c  \
           ./monitor.c  \
           ./mutex.c    \

HEADER = philosophers.h

LIBFT_DIR = ./LIBFT_DIR
LIBFT_FLAGS = -L $(LIBFT_DIR) -lft

OBJS = $(SRCS:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
RM = rm -r

all: createlibft $(NAME)

createlibft:
        @echo "Building libft..."
        @make -C $(LIBFT_DIR)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
        $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
        @echo "Compiling executable..."

clean:
	rm -f $(OBJS)
        rm -f $(LIBFT_DIR)/*.o

fclean: clean
        rm -f $(NAME)
        rm -f $(LIBFT_DIR)/libft.a

re:     fclean all

.PHONY: all clean fclean re

