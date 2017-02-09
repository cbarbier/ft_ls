# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgengo <jgengo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/18 14:05:46 by jgengo            #+#    #+#              #
#    Updated: 2017/02/09 13:29:55 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls
LIB				= libft/libft.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
SRCS			= srcs/ls_parse.c \
				  srcs/ls_argtolist.c \
				  srcs/ls_ftolist.c \
				  srcs/ls_sort.c \
				  srcs/ls_print_file.c \
				  srcs/ls_print_l.c \
				  srcs/ls_core.c \
				  srcs/ls_tools.c \
				  srcs/ft_ls.c

OBJS			= $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	gcc $(CFLAGS) -c $< -I includes -o $@

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft

$(LIB):
	make -C libft

clean:
	/bin/rm -f $(OBJS)
	make -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LIB)

re: fclean all

.PHONY: clean fclean all re
