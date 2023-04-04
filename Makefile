# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbax <jbax@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/17 18:03:37 by jbax          #+#    #+#                  #
#    Updated: 2023/03/31 17:16:17 by avon-ben      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH= expender : executor : files : lexer : headers : parser

NAME= minishell

SRC= readline.c signals.c main.c pwd.c what_cmd.c ft_cd.c\
	echo.c export.c environment.c unset.c exit.c execve.c\
	envget.c letspipe.c heredoc.c openfiles.c wildcard.c\
	parse_input.c parse_quotes.c parsing_list.c\
	parsing_tools.c tokanize_tools.c fill_node.c\
	list.c parse_splitter.c

OBF_DIR= OBF
	
OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

HEADER= builtins_data_struct.h all.h structures.h

lib=libft/libft.a

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

RLINE= -lreadline -L ~/.brew/opt/readline/lib/ $(lib)

SAN= -fsanitize=address

OO= -O3

all:$(NAME)

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE) 

$(OBF_DIR)/%o: %c $(HEADER) $(lib)
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/ -I $(lib)

$(lib):
	$(MAKE) -C libft bonus

$(OBF_DIR):
	mkdir $(OBF_DIR)

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

Norm: $(SRC) $(HEADER)
	norminette $^

.PHONY: all re fclean clean f norm

