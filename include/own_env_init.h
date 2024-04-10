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

void init_host(env_list_t **env);

static void (*OWN_INIT[])(env_list_t **) = {
    init_host,
};

static const size_t NB_OF_OWN_VARIABLES = sizeof(OWN_INIT) / sizeof(void *);

#endif
