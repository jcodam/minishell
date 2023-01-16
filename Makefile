NAME= minishell

SRC= readline.c signals.c main.c

OBF= $(SRC:%.c=$(OBF_DIR)/%.o) $(UTIL:%.c=$(OBF_DIR)/%.o)

HEADER= builtins_data_struct.h all.h

UTIL=

lib=libft.a

OBF_DIR= OBF

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

#USER= Users/curent_user/ = ~/
RLINE= -lreadline -L ~/.brew/opt/readline/lib/

SAN= -fsanitize=adres

OO= -O3


all:$(NAME)

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE)

$(lib):

$(OBF_DIR):
	mkdir $(OBF_DIR)

$(OBF_DIR)/%o: %c $(HEADER)
	$(CC) -c $(CFLAGS) $@ $<

clean:
	@rm -f $(OBF) $(OBF_DIR)

fclean:
	@rm -rf $(OBF) $(OBF_DIR) $(NAME)

f: fclean

r:$(NAME)
	./$(NAME)
re:
	@$(MAKE) fclean
	@$(MAKE) all

Norm:
	norminette $(SRC) $(HEADER)

.PHONY: all re fclean clean f norm

