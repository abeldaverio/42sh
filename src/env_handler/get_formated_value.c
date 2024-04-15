/*
** EPITECH PROJECT, 2024
** get formated value
** File description:
** get
*/

#include <string.h>
#include "env.h"
#include "functions.h"

char **get_formated_value(char *variable, env_list_t **env)
{
    if (*env == NULL)
        return NULL;
    if (strcmp((*env)->variable, variable) == 0) {
        return format_arguments((*env)->value, ":", "");
    }
    return get_formated_value(variable, &(*env)->next);
}
