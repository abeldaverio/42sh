/*
** EPITECH PROJECT, 2024
** init own env
** File description:
** init own env if env -i
*/

#include <stdbool.h>
#include "env.h"
#include "own_env_init.h"

bool init_own_env(env_list_t **env)
{
    for (size_t i = 0; i < NB_OF_OWN_VARIABLES; ++i) {
        if (!OWN_INIT[i](env))
            return false;
    }
    return true;
}
