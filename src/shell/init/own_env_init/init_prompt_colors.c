/*
** EPITECH PROJECT, 2024
** init prompt color
** File description:
** init the env varible for prompt colors
*/

#include "functions.h"
#include "env.h"

bool init_prompt_colors(env_list_t **env)
{
    insert_in_env("PROMPT_COLORS",
        "[0;31m:[0;35m:[34m:[32m:[0;31m:[33m", env);
    return true;
}
