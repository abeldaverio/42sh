/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_right
*/

#include <stdio.h>

void cursor_forward(char *line)
{
    dprintf(1, "\033[%dD", 1);
}