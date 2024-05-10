/*
** EPITECH PROJECT, 2024
** vector init
** File description:
** vector init
*/

#include "vector.h"
#include <stdlib.h>

void *vector_init(size_t size_of)
{
    vector_t *vector = calloc(1, sizeof(vector_t) +
        size_of * VECTOR_INIT_SIZE);

    if (vector == NULL)
        return NULL;
    vector->max = VECTOR_INIT_SIZE;
    vector->current = 0;
    vector->size = size_of;
    return (char *)vector + sizeof(vector_t);
}
