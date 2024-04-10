/*
** EPITECH PROJECT, 2024
** unse env
** File description:
** remove a variable from the env
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "built_in.h"
#include "functions.h"
#include "env.h"

static void remove_node(env_list_t **env_list)
{
    env_list_t *tmp = *env_list;

    free((*env_list)->variable);
    free((*env_list)->value);
    *env_list = (*env_list)->next;
    free(tmp);
}

static void remove_from_env(char *variable, env_list_t **env_list)
{
    if (*env_list == NULL)
        return;
    if (strcmp(variable, (*env_list)->variable) == 0) {
        remove_node(env_list);
        return;
    }
    remove_from_env(variable, &(*env_list)->next);
}

void unset_env(char **argv, env_t *env)
{
    if (my_arraylen(argv) < 2) {
        dprintf(2, "unsetenv: Too few arguments.\n");
        env->last_return = 1;
        return;
    }
    for (int i = 1; argv[i] != NULL; i++)
        remove_from_env(argv[i], env->env_list);
    env->last_return = 0;
    return;
}
