/*
** EPITECH PROJECT, 2024
** free
** File description:
** free env
*/

#include <stdlib.h>
#include "env.h"

static void free_env_list(env_list_t **env_list)
{
    if (*env_list == NULL)
        return;
    free_env_list(&(*env_list)->next);
    free((*env_list)->variable);
    free((*env_list)->value);
    free(*env_list);
}

void free_env(env_t *env)
{
    free_env_list(env->env_list);
    free_env_list(env->shell_variables);
    free_env_list(env->aliases);
    free(env->shell_variables);
    free(env->aliases);
    free(env->old_pwd);
    free(env->env_list);
    free_history(env->history);
    free(env);
}
