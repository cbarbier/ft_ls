# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgengo <jgengo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/18 14:05:46 by jgengo            #+#    #+#              #
#    Updated: 2017/02/01 15:04:37 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls
LIB				= libft/libft.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
SRCS			= srcs/main.c

all: $(NAME)

$(NAME): $(LIB) $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) -Llibft -lft $(MLX)

$(LIB):
	make -C libft

clean:
	make -C libft clean

fclean: clean
	/bin/rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
