/*
** EPITECH PROJECT, 2024
** not comand
** File description:
** handle lines that are not shell command
*/

#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include "functions.h"
#include "env.h"

static bool check_type(char *arg, env_t *env)
{
    struct stat sb;

    if (lstat(arg, &sb) == -1) {
        dprintf(1, "%s", arg);
        dprintf(1, ": Command not found.\n");
        env->last_return = 1;
        return false;
    }
    return true;
}

bool always_true(char **)
{
    return true;
}

void check_first_arg(char **args, env_t *env)
{
    if (!check_type(args[0], env))
        return;
    execute_file(args[0], args, env);
}
