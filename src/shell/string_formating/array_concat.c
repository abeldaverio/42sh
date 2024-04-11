/*
** EPITECH PROJECT, 2024
** arrayconcat
** File description:
** concatenate 2 arrays
*/

#include <stddef.h>
#include <stdlib.h>
#include "functions.h"

char **array_concat(char **first, char **second)
{
    size_t size = my_arraylen(first) + my_arraylen(second);
    char **new = calloc(sizeof(char *), size + 1);
    size_t i = 0;

    for (int j = 0; first[j]; j++) {
        new[i] = first[j];
        i++;
    }
    for (int j = 0; second[j]; j++) {
        new[i] = second[j];
        i++;
    }
    return new;
}
