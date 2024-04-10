/*
** EPITECH PROJECT, 2024
** search in env
** File description:
** env search
*/

#include <stddef.h>
#include <string.h>
#include "env.h"

char *search_env_value(char *variable, env_list_t **env)
{
    if (*env == NULL)
        return NULL;
    if (strcmp(variable, (*env)->variable) == 0)
        return (*env)->value;
    return search_env_value(variable, &(*env)->next);
}
