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

    if (args[1] == NULL)
        return false;
    if (args[2] != NULL) {
        dprintf(2, "exit: Expression Syntax.\n");
        env->last_return = 1;
        return true;
    }
    value = strtol(args[1], &check, 10);
    if (strcmp(check, "") != 0) {
        printf("%s\n", check);
        dprintf(2, "exit: Expression Syntax.\n");
        env->last_return = 1;
        return true;
    }
    env->last_return = value;
    return false;
}
