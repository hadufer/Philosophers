# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hadufer <hadufer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/28 15:24:12 by hadufer           #+#    #+#              #
#    Updated: 2022/03/12 10:22:35 by hadufer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

SRCS	=	ft_usleep.c \
			main.c \
			parser_init.c \
			routine.c \
			thread.c \
			utils.c \
			ft_itoa.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean flcean re
