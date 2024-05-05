# Program name
NAME				=	philo

# Compiler and CFlags
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra -g
RM					=	rm -f

# Directories
INC					=	inc/
SRC_DIR				=	src/
OBJ_DIR				=	obj/

# Source Files
SRC					=	data_init.c \
						handle_threads_mutexes.c \
						monitor.c \
						parse_input.c \
						philo.c \
						print_status.c \
						protect_vars.c \
						sim_start.c \
						utils.c

SRCS				=	$(addprefix $(SRC_DIR), $(SRC))

# Object files
OBJ 				= 	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Build rules

all: 					$(NAME)

$(NAME): 				$(OBJ)
						@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:			$(SRC_DIR)%.c 
						@mkdir -p $(@D)
						@$(CC) $(CFLAGS) -c $< -o $@

clean:
						@$(RM) -r $(OBJ_DIR)

fclean: 				clean
						@$(RM) $(NAME)
						@$(RM) src/a.out

re: 					fclean all

# Phony targets represent actions not files
.PHONY: 				all clean fclean re leaks valgrind_leaks help

# Checks for memory leaks
leaks: re
	@echo "\033[1;33m\nChecking for memory leaks...\033[0m"
	leaks --atExit -- ./$(NAME) 5 800 200 200 3

valgrind_leaks: re
	@echo "\033[1;33m\nChecking for memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME) 5 800 200 200 3

help:
	@echo "\033[1;35mMake options:\033[0m"
	@echo "\033[1;36mmake all\033[0m   Compile the program"
	@echo "\033[1;36mmake clean\033[0m   Remove object files"
	@echo "\033[1;36mmake fclean\033[0m   Remove object files and the executable"
	@echo "\033[1;36mmake re\033[0m   Re-build program from fresh after fclean"
	@echo "\033[1;36mmake leaks\033[0m   Check for memory leaks in macOS"
	@echo "\033[1;36mmake valgrind_leaks\033[0m   Check for leaks with valgrind in linux"
