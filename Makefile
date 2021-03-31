NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
LIB = libft/libft.a
SRC = 	./parsing/get_next_line.c\
	  	./parsing/get_next_line_utils.c\
	  	./parsing/parser.c\
	  	./parsing/check_errors.c\
	  	./parsing/check_flags.c\
	  	./parsing/ft_error.c\
	  	./parsing/get_structs.c\
	  	./parsing/get_env.c\
	  	./parsing/create_lists_prs.c\
	  	./parsing/get_dollars.c\
	  	./parsing/get_cmd_arg.c\
	  	./parsing/get_files.c\
	  	./parsing/outils.c\
		./parsing/check_flgs_sdr.c\
	  	./execution/builtin.c\
	  	./execution/execution.c\
	  	./execution/export_beta.c\
	  	./execution/linked_list.c\
		./execution/echo.c

OBJ = $(SRC:.c=.o)

magenta = `tput setaf 5`
white = `tput setaf 7`
bold = $(shell tput bold)
ED = \033[0m
all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "$(white)${bold}LIBRARY CREATION${ED}"
	@echo "$(white)${bold}... DONE ...${ED}"

%.o : %.c
	@echo "${bold}${white}COMPILING SRC...[OK]${ED}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "${bold}${magenta}REMOVE LIBRARY...[OK]${ED}"
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@echo "${bold}${magenta}REMOVE EXECUTION...[OK]${ED}"
	@make -C libft fclean

re: fclean all
