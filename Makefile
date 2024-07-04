# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 17:50:33 by lglauch           #+#    #+#              #
#    Updated: 2024/07/03 13:40:45 by rchavez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS	:= -Wextra -Wall -Werror

CC := cc

LIB := ./MLibft

LIBFT := ./MLibft/libft.a


SRCS	:= src/main.c src/globals.c src/utils.c src/ft_split_args.c\
src/signals.c src/path.c src/ft_error.c src/utils2.c src/envp.c src/expand2.c\
src/t_lexer.c src/t_file.c src/io_handler.c src/execute.c src/free_all.c\
src/get_line.c src/heredoc.c src/builtins/cd.c src/builtins/check_builtins.c\
src/builtins/echo.c src/builtins/env.c src/builtins/export.c\
src/builtins/pwd.c src/builtins/unset.c src/builtins/exit.c src/helper.c\
src/init_err.c

OBJS	:= ${SRCS:src%.c=obj%.o}

OBJ_F := obj

OBJ_FB := obj/builtins

all: $(OBJ_FB) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT) : $(LIB)
	cd $(LIB) && make

$(LIB) :
	@touch .gitmodules
	@git submodule add -f https://github.com/rodalcham/MLibft.git
	
$(OBJ_F) : 
	@if [ ! -d $(OBJ_F) ]; then \
		mkdir $(OBJ_F); \
	fi

$(OBJ_FB) : $(OBJ_F)
	@if [ ! -d $(OBJ_FB) ]; then \
		mkdir $(OBJ_FB); \
	fi

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@if [ -d "$(LIB)" ]; then \
		cd $(LIB) && make clean; \
	else \
		echo "Directory '$(LIB)' cannot be cleaned"; \
	fi
	rm -rf $(OBJ_F)

fclean: clean
	@if [ -d "$(LIB)" ]; then \
		rm -fr $(LIB); \
	else \
		echo "Directory '$(LIB)' cannot be removed."; \
	fi
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g -O0
debug: fclean all

run: all
	./minishell

PHONY : all, clean, fclean, re, run
