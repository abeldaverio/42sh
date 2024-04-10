/*
** EPITECH PROJECT, 2024
** set env
** File description:
** add or replace env
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "functions.h"
#include "env.h"
#include "built_in.h"

static bool is_str_alphanumeric(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (!(('a' <= str[i] && str[i] <= 'z') ||
            ('A' <= str[i] && str[i] <= 'Z') ||
            ('0' <= str[i] && str[i] <= '9') || str[i] == '_'))
            return false;
    return true;
}

static bool is_letter(char c)
{
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
        return true;
    return false;
}

static bool check_error(char **argv)
{
    if (my_arraylen(argv) > 3) {
        dprintf(2, "setenv: Too many arguments.\n");
        return true;
    }
    if (!(is_letter(argv[1][0]) || argv[1][0] == '_')) {
        dprintf(2, "setenv: ");
        dprintf(2, "Variable name must begin with a letter.\n");
        return true;
    }
    if (!is_str_alphanumeric(argv[1])) {
        dprintf(2, "setenv: Variable ");
        dprintf(2, "name must contain alphanumeric characters.\n");
        return true;
    }
    return false;
}

bool set_env(char **argv, env_t *env)
{
    if (my_arraylen(argv) == 1) {
        return display_env(argv, env);
    }
    if (check_error(argv)) {
        env->last_return = 1;
        return true;
    } else
        insert_in_env(argv[1], argv[2], env->env_list);
    env->last_return = 0;
    return true;
}
