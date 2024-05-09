/*
** EPITECH PROJECT, 2024
** exit
** File description:
** ctrl d
*/

#include "stdio.h"
#include "prompt.h"
#include "env.h"
#include "complete.h"

size_t handle_exit(prompt_t *prompt, env_t *env)
{
    reset_autocompletion(prompt, env);
    if (prompt->tty == 1)
        dprintf(1, "\n");
    return -1;
}
