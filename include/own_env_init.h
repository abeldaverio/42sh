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
bool init_shlvl(env_list_t **env);
bool init_vendor(env_list_t **env);
bool init_pwd(env_list_t **env);
bool init_prompt(env_list_t **env);

static bool (*OWN_INIT[])(env_list_t **) = {
    init_utsname,
    init_user,
    init_shlvl,
    init_vendor,
    init_pwd,
    init_prompt,
};

static const size_t NB_OF_OWN_VARIABLES = sizeof(OWN_INIT) / sizeof(void *);

#endif
