/*
** EPITECH PROJECT, 2024
** start shell
** File description:
** start shell
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "env.h"
#include "history.h"
#include "functions.h"
#include "macros.h"

bool handle_input(char *input, env_t *env)
{
    if (input == NULL)
        exit(84);
    if (start_tree(env, input)) {
        free(input);
        return true;
    }
    free(input);
    return false;
}

static void start_loop(env_t *env, int tty)
{
    int size = 0;
    size_t prompt_size = 0;
    char *input = NULL;
    char *new_input = NULL;

    prompt_size = print_prompt(env, tty);
    size = display_changes(env, prompt_size, &input, tty);
    while ((size != -1)) {
        if (!add_command_history(input, &(env->history))) {
            env->last_return = 1;
            break;
        }
        new_input = clear_special(input);
        if (handle_input(new_input, env))
            break;
        prompt_size = print_prompt(env, tty);
        size = display_changes(env, prompt_size, &input, tty);
    }
    if (input != NULL)
        free(input);
}

int start_shell(char const **env)
{
    env_t *env_struct = init_env(env);
    int return_value = 0;
    int tty = isatty(0);

    if (env_struct == NULL)
        return ERROR_STATUS;
    if (!signal_handler())
        return ERROR_STATUS;
    execute_rc(env_struct);
    start_loop(env_struct, tty);
    return_value = env_struct->last_return;
    free_env(env_struct);
    return return_value;
}
