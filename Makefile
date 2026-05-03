# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecakiray <ecakiray@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/27 11:52:31 by ecakiray          #+#    #+#              #
#    Updated: 2026/05/03 12:17:00 by ecakiray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCS = ft_printf.c ft_types.c
HDRS = ft_printf.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
ARFL = ar -rcs
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJS)
	$(ARFL) $(NAME) $(OBJS)

$(OBJS): $(HDRS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
