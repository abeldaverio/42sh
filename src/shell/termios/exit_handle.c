/*
** EPITECH PROJECT, 2024
** exit
** File description:
** ctrl d
*/

#include "stdio.h"
#include "prompt.h"

size_t handle_exit(prompt_t *prompt)
{
    if (prompt->tty == 1)
        dprintf(1, "\n");
    return -1;
}
