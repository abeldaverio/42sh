/*
** EPITECH PROJECT, 2024
** shell variable gestion
** File description:
** hum
*/

#include <stdbool.h>
#include <stdlib.h>
#include "macros.h"
#include "env.h"
#include "functions.h"

bool is_it_variable(char **args)
{
    for (int i = 0; args[0][i] != '\0'; i++)
        if (args[0][i] == '=')
            return true;
    return false;
}

bool set_variable(char **args, env_t *env)
{
    char **tmp = separate_line(args[0]);

    if (tmp == NULL)
        exit(ERROR_STATUS);
    insert_in_env(tmp[0], tmp[1], env->shell_variables);
    env->last_return = 0;
    free_array(tmp);
    if (my_arraylen(args) > 1)
        execute(my_arraydup(args + 1), env);
    return true;
}
