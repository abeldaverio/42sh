/*
** EPITECH PROJECT, 2024
** replace aliases
** File description:
** replace aliases
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "macros.h"
#include "env.h"

static bool replace_array(char ***args, char **check, env_list_t **aliases)
{
    char *alias_value = search_env_value(**args, aliases);
    char **formated_alias = NULL;
    char **new_args = NULL;

    if (alias_value == NULL)
        return false;
    formated_alias = format_arguments(alias_value, " \t\n", "\"\'");
    if (formated_alias == NULL)
        exit(ERROR_STATUS);
    if (is_string_in_array(formated_alias[0], CONST_A(check))) {
        free_array(formated_alias);
        return false;
    }
    check[my_arraylen(CONST_A(check))] = **args;
    new_args = array_concat(formated_alias, *args + 1);
    free(*args);
    free(formated_alias);
    *args = new_args;
    return true;
}

void replace_aliases(char ***args, env_list_t **aliases)
{
    char **check = calloc(sizeof(char *), 2);
    size_t len = 0;

    if (check == NULL)
        return;
    while (replace_array(args, check, aliases)) {
        len = my_arraylen(CONST_A(check));
        check = reallocarray(check, my_arraylen(CONST_A(check)) + 2, sizeof(char *));
        check[len + 1] = NULL;
        if (check == NULL)
            return;
    }
    free_array(check);
}
