/*
** EPITECH PROJECT, 2024
** append to variable.c
** File description:
** append to varible with +=
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"
#include "macros.h"
#include "env.h"

bool is_it_append_variable(char **args)
{
    for (int i = 0; args[0][i] != '\0'; i++)
        if (args[0][i] == '+' && args[0][i + 1] == '=')
            return true;
    return false;
}

static bool append_value(char **tmp, env_list_t **env)
{
    char *value = search_env_value(tmp[0], env);
    char *result = NULL;

    if (value == NULL) {
        insert_in_env(tmp[0], tmp[1], env);
        return true;
    }
    result = my_strcat(2, value, tmp[1]);
    if (result == NULL)
        return false;
    insert_in_env(tmp[0], result, env);
    free(result);
    return true;
}

static bool distribute(char *value, char **tmp, env_t *env)
{
    if (value != NULL) {
        if (!append_value(tmp, env->env_list)) {
            free_array(tmp);
            env->last_return = 84;
            return false;
        }
    } else {
        if (!append_value(tmp, env->shell_variables)) {
            free_array(tmp);
            env->last_return = 84;
            return false;
        }
    }
    return true;
}

bool append_to_variable(char **args, env_t *env)
{
    char **tmp = separate_line(args[0]);
    char *value = NULL;

    if (tmp == NULL) {
        env->last_return = ERROR_STATUS;
        return false;
    }
    tmp[0][strlen(tmp[0]) - 1] = '\0';
    value = search_env_value(tmp[0], env->env_list);
    if (!distribute(value, tmp, env))
        return false;
    free_array(tmp);
    env->last_return = 0;
    return true;
}
