/*
** EPITECH PROJECT, 2024
** unset alias
** File description:
** rm the alias
*/

#include <stdbool.h>
#include <stdio.h>
#include "env.h"
#include "functions.h"
#include "macros.h"

bool unset_alias(char **argv, env_t *env)
{
    if (my_arraylen(CONST_A(argv)) < 2) {
        dprintf(2, "unalias: Too few arguments.\n");
        env->last_return = 1;
        return true;
    }
    for (int i = 1; argv[i] != NULL; i++)
        remove_from_env(argv[i], env->aliases);
    env->last_return = 0;
    return true;
}
