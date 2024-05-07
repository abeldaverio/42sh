/*
** EPITECH PROJECT, 2024
** vector push
** File description:
** vector push
*/

#include "vector.h"
#include <stdio.h>
#include <string.h>

void vector_push(void *data, size_t index, void *c)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    void *current = NULL;

    if (index > vector->current) {
        return;
    }
    if (vector->current + 1 >= vector->max) {
        vector_resize(&vector, (vector)->max * 2);
        *(void **)data = (char *)vector + sizeof(vector_t);
    }
    current = (*(void **)data) + ((vector)->size) * index;
    memmove(current + vector->size, current, (vector->current - index) *
        vector->size);
    vector_set(data, index, c);
    (vector)->current++;
}
