/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_del
*/

#include <stdio.h>
#include "macros.h"
#include "vector.h"

void delete(size_t i)
{
    dprintf(1, "\033[%dE", 1);
}

size_t delete_command(size_t index, char **line)
{
    if (index <= 0)
        return index;
    vector_delete(line, index - 1);
    return index - 1;
}
