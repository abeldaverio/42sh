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
				get_env_array.c	\
				insert_int_in_env.c	\
				get_formated_value.c	\
			)	\
			$(addprefix error_handling/,\
				check_arguments.c	\
			)	\
			$(addprefix free/,\
				free_env.c	\
				free_array.c	\
			)	\
			$(addprefix parser/,\
				checkers.c	\
				file_redirections.c	\
				ll_decoder.c	\
				ll_parser.c	\
				symbols_handling.c	\
				request_input.c	\
			)	\
			$(addprefix shell/,\
				$(addprefix init/,\
					$(addprefix own_env_init/,\
						init_host.c	\
						init_own_env.c	\
						init_user.c	\
						init_shlvl.c	\
						init_vendor.c	\
						init_pwd.c	\
						init_prompt_colors.c	\
					)	\
					init_env.c	\
				)	\
				$(addprefix string_formating/,\
					format_arguments.c	\
					clear_special.c	\
					array_concat.c 	\
					replace_aliases.c	\
					star_formating.c	\
				)	\
				$(addprefix execute/,\
					$(addprefix built_in/,\
						change_directory.c	\
						set_env.c	\
						set_variable.c	\
						unset_env.c	\
						display_env.c	\
						exit.c	\
						set_alias.c	\
						unset_alias.c	\
						append_to_variable.c	\
						camille_fetch.c	\
						$(addprefix fetch/,\
							fetch_command.c	\
							fetch_hardware.c	\
							fetch_usr_info.c	\
							fetch_window_info.c	\
							fetch_memory.c	\
						)	\
					)	\
					default.c	\
					execute_command.c	\
					find.c	\
					execute_file.c	\
					last_return.c	\
					try_execute.c	\
				)	\
				start_shell.c	\
			)	\
			$(addprefix print/,\
				print_prompt.c	\
			)	\
			$(addprefix side_functions/,\
				int_to_str.c	\
				my_arraydup.c	\
				my_arraylen.c	\
				my_strcat.c	\
				is_string_in_array.c	\
			)	\
		)	\

SRC_TEST	=	$(addprefix tests/,\
			redirect.c	\
			)

SRC_TO_TEST	=	$(filter-out src/main.c, $(SRC))

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

fclean:	clean tests_clean
	$(RM) $(NAME)

re:	fclean all

debug: CFLAGS += -g
debug: re

asan: CC = clang -fsanitize=address
asan: re

$(TEST_NAME):	$(OBJ_TEST)
	$(CC) -o $(TEST_NAME) $(CFLAGS) $(CPPFLAGS)	\
	$(OBJ_TEST) $(SRC_TO_TEST)	\
	$(TEST_FLAGS) $(TEST_LIB)

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
