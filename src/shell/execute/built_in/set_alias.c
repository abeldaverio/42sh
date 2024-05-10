/*
** EPITECH PROJECT, 2024
** set alias
** File description:
** set alias
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "possibility.h"
#include "macros.h"
#include "env.h"

static bool print_aliases(env_list_t **aliases, char *alias)
{
    if (*aliases == NULL)
        return (alias == NULL) ? true : false;
    if (alias == NULL || strcmp(alias, (*aliases)->variable) == 0) {
        dprintf(1, "alias %s='%s'\n",
            (*aliases)->variable, (*aliases)->value);
        if (alias != NULL)
            return true;
    }
    return print_aliases(&(*aliases)->next, alias);
}

static void insert_alias(env_list_t **aliases, char *arg)
{
    char **tmp = separate_line(arg);

    if (tmp == NULL)
        exit(ERROR_STATUS);
    for (int i = 0; tmp[0][i]; ++i) {
        if (tmp[0][i] == ' ' || tmp[0][i] == '\t' || tmp[0][i] == '\n') {
            dprintf(2, "'%s': invalid alias name\n", tmp[0]);
            free_array(tmp);
            return;
        }
    }
    insert_in_env(tmp[0], tmp[1], aliases);
    free_array(tmp);
}

static int handle_alias(env_list_t **aliases, char **arg)
{
    if (is_it_variable(arg)) {
        insert_alias(aliases, arg[0]);
        return 0;
    } else {
        if (!print_aliases(aliases, arg[0])) {
            dprintf(2, "alias: %s: not found\n", *arg);
            return 1;
        }
    }
    if (my_arraylen(CONST_A(arg)) > 1)
        return handle_alias(aliases, arg + 1);
    return 0;
}

bool set_alias(char **args, env_t *env)
{
    if (my_arraylen(CONST_A(args)) == 1) {
        print_aliases(env->aliases, NULL);
        env->last_return = 0;
    } else {
        env->last_return = handle_alias(env->aliases, args + 1);
    }
    return true;
}
