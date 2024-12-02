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

OBJS = $(SRCS:.c=.o)

HEAD = philosophers.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -r

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
        $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
        rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re

