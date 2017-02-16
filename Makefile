# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgengo <jgengo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/18 14:05:46 by jgengo            #+#    #+#              #
#    Updated: 2017/02/16 13:59:23 by cbarbier         ###   ########.fr        #
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
				  srcs/ls_print_c.c \
				  srcs/ls_core.c \
				  srcs/ls_tools.c \
				  srcs/ls_tools2.c \
				  srcs/ft_ls.c

OBJS			= $(SRCS:.c=.o)

	
all: display $(NAME)

display:
	@echo "\n\n"
	@echo "\033[35;1m ____   _____         _       ____ \033[0m"
	@echo "\033[35;1m|  _ | |_   _|       | |     |   _|\033[0m"
	@echo "\033[35;1m| |__    | |         | |     |   \ \033[0m"
	@echo "\033[35;1m|  __|   | |   ____  | |__    _\  |\033[0m"
	@echo "\033[35;1m|_|      |_|  |____| |____|  |____|\033[0m\n\n"
	@echo "By : \033[0;35mcbarbier@student.42.fr\033[0m"
%.o:%.c
	@gcc $(CFLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft
	@echo "FT_LS COMPILED\t\t\033[0;32m✓\033[0m"
$(LIB):
	@make -C libft

clean:
	@make -C libft clean
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(LIB)
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
