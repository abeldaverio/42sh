/*
** EPITECH PROJECT, 2024
** print prompt
** File description:
** print the prompt
*/

#include <stdio.h>
#include "env.h"
#include "functions.h"
#include "colors.h"

static char *get_dir(char *pwd)
{
    int last_slash = 0;

    if (pwd == NULL)
        return NULL;
    for (int i = 0; pwd[i] != '\0'; i++)
        if (pwd[i] == '/')
            last_slash = (i == 0) ? i : i + 1;
    return pwd + last_slash;
}

void print_prompt(env_t *env)
{
    char *username = search_env_value("USER", env->env_list);
    char *version = search_env_value("HOSTNAME", env->env_list);
    char *dir = get_dir(search_env_value("PWD", env->env_list));

    dprintf(1, "%s%s%s@", RED, ((username == NULL) ? "" : username),
        DEFAULT);
    dprintf(1, "%s%s%s:", PURPLE, ((version == NULL) ? "" : version), DEFAULT);
    dprintf(1, "%s%s%s", BLUE, ((dir == NULL) ? "" : dir), DEFAULT);
    if (env->last_return == 0)
        dprintf(1, " > %s%ld%s ", GREEN, env->last_return, DEFAULT);
    else
        dprintf(1, " > %s%ld%s ", RED, env->last_return, DEFAULT);
    dprintf(1, "%s$>%s ", YELLOW, DEFAULT);
}
