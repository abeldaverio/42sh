/*
** EPITECH PROJECT, 2024
** init shlvl
** File description:
** count the number of shell oppend
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "env.h"

bool init_shlvl(env_list_t **env)
{
    char *value = search_env_value("SHLVL", env);
    char *check = NULL;
    int n = 0;

    if (value == NULL) {
        insert_in_env("SHLVL", "1", env);
        return true;
    }
    n = strtol(value, &check, 10);
    if (strcmp(check, "") != 0) {
        insert_in_env("SHLVL", "1", env);
        return true;
    }
    insert_int_in_env("SHLVL", n + 1, env);
    return true;
}
