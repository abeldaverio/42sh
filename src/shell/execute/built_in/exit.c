/*
** EPITECH PROJECT, 2024
** handle line
** File description:
** handle a command line
*/

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "functions.h"

bool set_exit_value(char **args, env_t *env)
{
    char *check = NULL;
    int value = 0;

    if (args[2] != NULL)
        return false;
    if (args[3] != NULL) {
        dprintf(2, "exit: Expression Syntax.\n");
        env->last_return = 1;
        return true;
    }
    value = strtol(args[1], &check, 10);
    if (check != NULL) {
        dprintf(2, "exit: Expression Syntax.\n");
        env->last_return = 1;
    }
    env->last_return = value;
    return false;
}
