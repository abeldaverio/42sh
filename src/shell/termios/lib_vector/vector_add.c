/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

void vector_add(void *data, void *c)
{
    vector_t *vector = NULL;
    void *current = NULL;

    if ((data) == NULL || c == NULL)
        return;
    vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    if ((vector)->current >= (vector)->max) {
        vector_resize(&vector, (vector)->max * 2);
        *(void **)data = (char *)vector + sizeof(vector_t);
    }
    current = (*(void **)data) + ((vector)->size) * (vector)->current;
    memcpy(current, c, vector->size);
    (vector)->current++;
}

char *str_to_vector(char *str)
{
    char *tmp = NULL;

    if (str == NULL)
        return NULL;
    tmp = vector_init(sizeof(char));
    if (tmp == NULL)
        return NULL;
    for (int i = 0; str[i]; ++i) {
        vector_push(&tmp, i, &str[i]);
    }
    return tmp;
}

char *vector_to_str(void **data)
{
    vector_t *vector = NULL;
    char *result = NULL;

    if (data == NULL)
        return NULL;
    vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    result = calloc(sizeof(char), vector->current + 1);
    if (result == NULL)
        return NULL;
    strncpy(result, *data, vector->current);
    return result;
}
