/*
** EPITECH PROJECT, 2024
** my arraylen
** File description:
** array len
*/

#include <stddef.h>

int my_arraylen(char **array)
{
    int i;

    if (array == NULL)
        return 0;
    for (i = 0; array[i] != NULL; i++);
    return i;
}
