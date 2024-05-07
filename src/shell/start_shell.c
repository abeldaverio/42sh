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
#include "functions.h"

static bool handle_input(char *input, env_t *env)
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

// handle tty
static void start_loop(env_t *env, int tty, size_t prompt_size)
{
    size_t tmp = 0;
    int size = 0;
    char *input = NULL;
    char *new_input = NULL;

    size = display_changes(env, prompt_size, &input);
    while ((size != -1)) {
        new_input = clear_special(input);
        if (handle_input(new_input, env))
            break;
        print_prompt(env);
        size = display_changes(env, prompt_size, &input);
    }
    if (input != NULL)
        free(input);
}

int start_shell(char const **env)
{
    env_t *env_struct = init_env(env);
    int return_value;
    int tty = isatty(0);
    size_t prompt_size = 0;

    if (env_struct == NULL)
        return 84;
    if (tty == 1)
        prompt_size = print_prompt(env_struct);
    start_loop(env_struct, tty, prompt_size);
    return_value = env_struct->last_return;
    free_env(env_struct);
    return return_value;
}
