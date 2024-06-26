/*
** EPITECH PROJECT, 2024
** functions
** File description:
** functions for 42sh
*/

#ifndef FUNCTION_H
    #define FUNCTION_H

    #include <stdbool.h>
    #include "env.h"
    #include "prompt.h"

//error handling
bool check_main_args(int const argc);

//init
env_t *init_env(char const **env);
bool init_own_env(env_list_t **env);

//env functions
char *search_env_value(char *variable, env_list_t **env);
void insert_in_env(char *variable, char *value, env_list_t **env_list);
char **get_env_array(env_list_t **env_list);
void remove_from_env(char *variable, env_list_t **env_list);
void insert_int_in_env(char *variable, int int_value, env_list_t **env);
char **get_formated_value(char *variable, env_list_t **env);

//print functions
size_t print_prompt(env_t *env, int tty);
size_t display_changes(env_t *env, size_t prompt_size, char **input, int tty);

//main functions
int start_shell(char const **env);
bool handle_line(char **args, env_t *env);
bool execute(char **args, env_t *env);
void update_status(int status, env_t *env);
bool execute_file(char *executable, char **args, env_t *env);
void try_execute(char *path, char **args, char **env);
bool handle_input(char *input, env_t *env);
void execute_rc(env_t *env);

//string formating
char *clear_special(char *input);
char **format_arguments(char *line,
    const char *separators, const char *ignorer);
char **separate_line(char const *line);
void replace_aliases(char ***args, env_list_t **aliases);
char **array_concat(char **, char **);

//free
void free_env(env_t *);
void free_array(char **);

//side functions
char *int_to_str(int);
char **my_arraydup(char const *const *const);
int my_arraylen(char const *const *const);
char *my_strcat(size_t size, ...);
bool is_string_in_array(char const *const str, char const *const *const array);
char **open_config_dir(char *dir, char *filter);
char my_getchar(void);

//parser
int start_tree(env_t *env, char *input);
void request_input(char **input, char const *img);
bool format_input(char ***input);
bool is_filename_valid(char *name, char *prefix, char *suffix);

//signal handling
bool signal_handler(void);

//autocomplete
int *auto_complete(char *input, int completion_ptr, int info[3]);

//keyboard
void print_input_line(prompt_t *prompt, env_t *env, bool del);

#endif
