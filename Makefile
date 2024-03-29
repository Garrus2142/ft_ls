# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thugo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 14:29:27 by thugo             #+#    #+#              #
#    Updated: 2017/02/20 13:28:05 by thugo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = ft_ls
LIBFT = libft.a

FILE_SRC = src/ft_ls.c src/args.c src/files.c src/stats.c src/display.c src/rights.c

OBJ = $(FILE_SRC:.c=.o)

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[34mCreation de $(NAME)...\033[0m"
	@gcc -Llibft -lft -o $(NAME) $(OBJ)
	@echo "\033[32mTermine\033[0m"

%.o: %.c
	@echo "\033[34mCompilation:\033[0m $^ \033[34m>\033[0m $@"
	@gcc $(FLAGS) -I includes -c $^ -o $@

clean:
	@echo "\033[31mSuppression des objets...\033[0m $@"
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@echo "\033[31mSuppression des binaires...\033[0m"
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
