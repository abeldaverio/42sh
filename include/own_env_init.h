/*
** EPITECH PROJECT, 2024
** own env init
** File description:
** init own env
*/

#ifndef OWN_ENV_H
    #define OWN_ENV_H

    #include <stdbool.h>
    #include <stddef.h>
    #include "env.h"

bool init_utsname(env_list_t **env);
bool init_user(env_list_t **env);

static bool (*OWN_INIT[])(env_list_t **) = {
    init_utsname,
    init_user,
};

static const size_t NB_OF_OWN_VARIABLES = sizeof(OWN_INIT) / sizeof(void *);

#endif
