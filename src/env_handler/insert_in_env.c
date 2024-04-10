/*
** EPITECH PROJECT, 2024
** insert in env
** File description:
** insert
*/

#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "env.h"

static env_list_t *init_env_node(char *variable, char *value)
{
    env_list_t *env = calloc(sizeof(env_list_t), 1);

    if (env == NULL)
        exit(ERROR_STATUS);
    env->variable = strdup(variable);
    env->value = strdup((value == NULL) ? "" : value);
    if (env->variable == NULL || env->value == NULL)
        exit(ERROR_STATUS);
    env->next = NULL;
    return env;
}

void insert_in_env(char *variable, char *value, env_list_t **env_list)
{
    if (*env_list == NULL) {
        *env_list = init_env_node(variable, value);
        return;
    }
    if (strcmp(variable, (*env_list)->variable) == 0) {
        free((*env_list)->value);
        (*env_list)->value = strdup((value == NULL) ? "" : value);
        if ((*env_list)->value == NULL)
            exit(ERROR_STATUS);
        return;
    }
    insert_in_env(variable, value, &(*env_list)->next);
}
