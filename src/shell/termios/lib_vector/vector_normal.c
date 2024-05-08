/*
** EPITECH PROJECT, 2024
** vector normal
** File description:
** vector normal
*/

#include <string.h>
#include "vector.h"

void vector_normal(void *data, void *c)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    size_t size = vector->size * vector->current;
    size_t size_of = vector->size;

    memmove(vector, *(void **)data, size);
    memcpy((void *)vector + size, c, size_of);
    *(void **)data = vector;
}
