/*
** EPITECH PROJECT, 2024
** set
** File description:
** set
*/

#include <string.h>
#include "vector.h"

void vector_set(void *data, size_t index, void *item)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));

    if (index > vector->current)
        return;
    memcpy((*(void **)data) + ((vector)->size) * index, item, vector->size);
}
