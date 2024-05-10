/*
** EPITECH PROJECT, 2024
** free
** File description:
** free
*/

#include "vector.h"
#include <stdlib.h>

void vector_free(void *data)
{
    if (data == NULL)
        return;
    data = data - sizeof(vector_t);
    free(data);
}
