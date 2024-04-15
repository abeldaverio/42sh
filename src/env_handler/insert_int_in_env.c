/*
** EPITECH PROJECT, 2024
** insert int in env
** File description:
** insert
*/

#include <stddef.h>
#include <stdlib.h>
#include "functions.h"
#include "macros.h"
#include "env.h"

void insert_int_in_env(char *variable, int int_value, env_list_t **env)
{
    char *value = int_to_str(int_value);

    if (value == NULL)
        exit(ERROR_STATUS);
    insert_in_env(variable, value, env);
    free(value);
}
