/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_del
*/

#include "macros.h"

void delete(char *line)
{
    dprintf(1, "\033[%dE", 1);
}

void delete_command(char *line)
{
    dprintf(1, "\b ");
    cursor_forward(line);
}