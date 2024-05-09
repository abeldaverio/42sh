/*
** EPITECH PROJECT, 2024
** resize
** File description:
** resize
*/

#include "vector.h"
#include <stdlib.h>

void vector_resize(vector_t **vector, size_t new)
{
    vector_t *new_vect = realloc(*vector, sizeof(vector_t) +
        new * (*vector)->size);

    if (new_vect != NULL)
        new_vect->max = new;
    *vector = new_vect;
}
