# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 17:50:33 by lglauch           #+#    #+#              #
#    Updated: 2024/05/20 16:47:26 by lglauch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS	:= -Wextra -Wall -Werror
CFLAGS	:= -Wextra -Wall -Werror -I/usr/local/opt/readline/include
SRCS	:= src/main.c src/globals.c src/utils.c src/ft_split_args.c src/tokenize.c src/signals.c src/path.c\
			libft/ft_split.c libft/ft_strlen.c libft/ft_strncmp.c
OBJS	:= ${SRCS:src/%.c=src/%.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ libft/libft.a -lreadline 

src/%.o: src/%.c
	@make -C libft
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C libft clean
	rm -rf src/*.o

fclean: clean
	@make -C libft fclean
	rm -rf $(NAME)

re: clean all

debug: CFLAGS += -g -O0
debug: fclean $(NAME)

run: $(NAME) 
	./minishell
