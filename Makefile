NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
LIB = libft/libft.a
SRC = ./parsing/get_next_line.c\
	  ./parsing/get_next_line_utils.c\
	  ./parsing/parser.c\
	  ./parsing/parse_utils.c\
	  ./parsing/check_flags.c\
	  ./parsing/ft_error.c\
	  ./parsing/get_structs.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

help:
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"

re: fclean all