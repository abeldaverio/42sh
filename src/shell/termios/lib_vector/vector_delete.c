/*
** EPITECH PROJECT, 2024
** delete
** File description:
** delete
*/

#include "vector.h"
#include <string.h>

void vector_delete(void *data, size_t index)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));

    if (index > vector->current)
        return;
    if (index + 1 < vector->current)
        memmove(*(void **) data + (index * vector->size), (*(void **) data) +
            ((index + 1) * vector->size), vector->size *
            (vector->current) - index);
    vector->current--;
}
