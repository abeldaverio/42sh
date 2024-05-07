/*
** EPITECH PROJECT, 2024
** check free
** File description:
** checks free
*/

#include <stdlib.h>

void check_free(void *ptr)
{
    if (ptr != NULL)
        free(ptr);
}
