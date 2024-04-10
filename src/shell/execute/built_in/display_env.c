/*
** EPITECH PROJECT, 2024
** display env
** File description:
** command env
*/

#include <stdio.h>
#include "env.h"
#include "functions.h"

static void print_env(env_list_t **env_list)
{
    if (*env_list == NULL)
        return;
    dprintf(1, "%s=%s\n", (*env_list)->variable, (*env_list)->value);
    print_env(&(*env_list)->next);
}

void display_env(char **argv, env_t *env)
{
    if (my_arraylen(argv) > 1) {
        dprintf(2, "env: Too many arguments.\n");
        env->last_return = 1;
        return;
    }
    print_env(env->env_list);
    env->last_return = 0;
}
