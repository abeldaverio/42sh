/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "vector.h"
#include <string.h>

void vector_add(void *data, void *c)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    void *current = NULL;

    if ((vector)->current >= (vector)->max) {
        vector_resize(&vector, (vector)->max * 2);
        *(void **)data = (char *)vector + sizeof(vector_t);
    }
    current = (*(void **)data) + ((vector)->size) * (vector)->current;
    memcpy(current, c, vector->size);
    (vector)->current++;
}
