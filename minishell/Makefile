NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g

CC = cc

SRC =	main.c \
		src/alloc/add_alloc.c \
		src/ft_lexer/lexer_errors.c \
		src/ft_lexer/lexer_main.c \
		src/ft_lexer/lexer_token.c \
		src/ft_lexer/lexer_utils.c \
		src/expender/expender.c \
		src/alloc/clear_alloc.c \
		src/execute/execute.c\
		src/command/env.c		\
		src/command/pwd.c		\
		src/command/exit.c		\
		src/command/echo.c		\
		src/command/export.c	\
		src/command/unset.c		\
		src/command/cd.c		\
		src/utils/utils.c		\
		src/utils/exit.c		\
		src/utils/redir.c		\
		src/utils/builtins.c	\
		src/signal/signal.c		\
		src/execute/config.c	\
		src/utils/executils.c	\

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

f : fclean

c : clean

re: fclean all

.PHONY: all clean fclean re f c
