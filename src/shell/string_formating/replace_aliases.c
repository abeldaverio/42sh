/*
** EPITECH PROJECT, 2024
** replace aliases
** File description:
** replace aliases
*/

#include <stdlib.h>
#include "functions.h"
#include "macros.h"
#include "env.h"

bool replace_aliases(char ***args, env_list_t **aliases)
{
    char *alias_value = search_env_value(**args, aliases);
    char **formated_alias = NULL;
    char **new_args = NULL;

    if (alias_value == NULL)
        return false;
    formated_alias = format_arguments(alias_value, " \t\n", "\"\'");
    if (formated_alias == NULL)
        exit(ERROR_STATUS);
    free(**args);
    new_args = array_concat(formated_alias, *args + 1);
    free(*args);
    free(formated_alias);
    *args = new_args;
    return strcmp(alias_value, **args) == 0 ? false : true;
}
