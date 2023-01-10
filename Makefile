NAME= minishell

SRC= 

OBF= $(SRC:%.c=$(OBF_DIR)/%.o) $(UTIL:%.c=$(OBF_DIR)/%.o)

HEADER= builtins_data_struct.h

UTIL=

lib=libft.a

OBF_DIR= OBF

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror -o

USER= jbax

RLINE= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib/

SAN= -fsanitize=adres

OO= -O3


all:$(NAME)

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF)

$(lib):

$(OBF_DIR):
	mkdir $(OBF_DIR)

$(OBF_DIR)%o: %c $(HEADERS)
	$(CC) -c $(CFLAGS) $@ $<

clean:
	@rm -f $(OBF) $(OBF_DIR)

fclean:
	@rm -rf $(OBF) $(OBF_DIR) $(NAME)

f: fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

norm:
	norminette $(SRC) $(UTIL) $(HEADERS)

.PHONY: all re fclean clean f norm

t:
	gcc $(CFLAGS) rr readline.c $(RLINE) 
	./rr
