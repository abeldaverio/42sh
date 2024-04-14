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

bool camille_fetch(char **, env_t *env)
{
    if (!fetch_command(env, CAMILLE))
        return false;
    return true;
}
