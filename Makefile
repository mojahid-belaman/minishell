NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc
LIB = libft/libft.a
SRC = 	./parsing/parser.c\
	  	./parsing/check_errors.c\
	  	./parsing/check_flags.c\
	  	./parsing/ft_error.c\
	  	./parsing/get_env.c\
	  	./parsing/create_lists_prs.c\
	  	./parsing/get_dollars.c\
	  	./parsing/get_cmd_arg.c\
	  	./parsing/get_files.c\
	  	./parsing/outils.c\
		./parsing/check_flgs_sdr.c\
		./parsing/read_line.c\
		./parsing/outils_readline.c\
		./parsing/signals_readline.c\
		./parsing/press_key.c\
		./parsing/hundel_error.c\
		./parsing/get_about_dollar.c\
	  	./execution/builtin.c\
	  	./execution/execution.c\
	  	./execution/execution_pipe.c\
	  	./execution/execution_beta.c\
	  	./execution/export.c\
	  	./execution/linked_list.c\
		./execution/echo.c\
		./execution/utils.c\
		./execution/builtin_beta.c\
		./execution/message_errors.c\
		./execution/export_beta.c

OBJ = $(SRC:.c=.o)

magenta = `tput setaf 5`
white = `tput setaf 7`
bold = $(shell tput bold)
ED = \033[0m
all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -lncurses -o $(NAME)
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
