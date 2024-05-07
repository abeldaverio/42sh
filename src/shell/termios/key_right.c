/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_right
*/

#include <stdio.h>

void cursor_forward(size_t i)
{
    dprintf(1, "\033[%ldC", i);
}
