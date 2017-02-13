# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgengo <jgengo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/18 14:05:46 by jgengo            #+#    #+#              #
#    Updated: 2017/02/12 16:20:19 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls
LIB				= libft/libft.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCLUDES		= -I includes -I libft/includes
SRCS			= srcs/ls_parse.c \
				  srcs/ls_argtolist.c \
				  srcs/ls_ftolist.c \
				  srcs/ls_sort.c \
				  srcs/ls_print.c \
				  srcs/ls_print_l.c \
				  srcs/ls_core.c \
				  srcs/ls_tools.c \
				  srcs/ft_ls.c

OBJS			= $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	gcc $(CFLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

$(LIB):
	make -C libft

clean:
	make -C libft clean
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(LIB)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
