/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_left
*/

#include <stddef.h>
#include <stdio.h>

void cursor_backward(size_t i)
{
    dprintf(1, "\033[%ldD", i);
}
