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
