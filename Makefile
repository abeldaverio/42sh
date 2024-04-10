##
## EPITECH PROJECT, 2023
## make file
## File description:
## makes stuff
##

SRC	=	$(addprefix src/,\
			main.c	\
			$(addprefix env_handler/,\
				insert_in_env.c	\
				search_in_env.c	\
			)	\
			$(addprefix error_handling/,\
				check_arguments.c	\
			)	\
			$(addprefix free/,\
				free_env.c	\
				free_array.c	\
			)	\
			$(addprefix shell/,\
				$(addprefix init/,\
					$(addprefix own_env_init/,\
						init_host.c	\
						init_own_env.c	\
					)	\
					init_env.c	\
				)	\
				$(addprefix string_formating/,\
					format_arguments.c	\
					clear_special.c	\
				)	\
				start_shell.c	\
				handle_line.c	\
			)	\
			$(addprefix print/,\
				print_prompt.c	\
			)	\
		)	\

CPPFLAGS	=	-iquote./include

CFLAGS	+=	-Wall -Wextra

TEST_FLAGS	=	--coverage

TEST_LIB	=	-lcriterion

CC	?=	gcc

OBJ	=	$(SRC:.c=.o)

OBJ_TEST	=	$(SRC_TEST:.c=.o)

NAME	=	42sh

TEST_NAME	=	unit_tests

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

debug: CFLAGS += -ggdb3
debug: re

asan: CC = clang -fsanitize=address
asan: re

$(TEST_NAME):	$(OBJ_TEST)
	$(CC) -o $(TEST_NAME) $(CFLAGS) $(CPPFLAGS)	\
	$(OBJ_TEST) $(SRC_TO_TEST)	\
	$(TEST_FLAGS)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)

tests_clean:
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) coverage*
	$(RM) unit_tests

coverage:
	gcovr --html-details coverage && firefox coverage

.PHONY: all clean fclean re debug tests_run coverage tests_clean asan
