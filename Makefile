# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbax <jbax@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/17 18:03:37 by jbax          #+#    #+#                  #
#    Updated: 2023/01/22 19:20:28 by avon-ben      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRC= readline.c signals.c main.c pwd.c what_cmd.c ft_cd.c\
	echo.c parse_input.c list.c 

OBF= $(SRC:%.c=$(OBF_DIR)/%.o) $(UTIL:%.c=$(OBF_DIR)/%.o)

HEADER= builtins_data_struct.h all.h

UTIL=

lib=libft/libft.a

OBF_DIR= OBF

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

RLINE= -lreadline -L ~/.brew/opt/readline/lib/ $(lib)

SAN= -fsanitize=adres

OO= -O3


all:$(NAME)

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE)

$(lib):
	$(MAKE) -C libft

$(OBF_DIR):
	mkdir $(OBF_DIR)

$(OBF_DIR)/%o: %c $(HEADER) $(lib)
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/ -I $(lib)

clean:
	@rm -f $(OBF) $(OBF_DIR)

fclean:
	@rm -rf $(OBF) $(OBF_DIR) $(NAME)
	$(MAKE) -C libft fclean

f: fclean

r:$(NAME)
	./$(NAME)
re:
	@$(MAKE) fclean
	@$(MAKE) all

Norm:
	norminette $(SRC) $(HEADER)

.PHONY: all re fclean clean f norm

