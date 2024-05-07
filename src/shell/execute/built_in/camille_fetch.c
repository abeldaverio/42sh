/*
** EPITECH PROJECT, 2024
** neofetch
** File description:
** neofetch
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "fetch_theme.h"
#include "fetch_info.h"
#include "functions.h"

bool camille_fetch(char **argv, env_t *env)
{
    if (!fetch_command(argv, env, CAMILLE))
        env->last_return = 1;
    else
        env->last_return = 0;
    return true;
}
