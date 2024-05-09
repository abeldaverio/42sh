/*
** EPITECH PROJECT, 2024
** total
** File description:
** total
*/

#include "vector.h"


size_t vector_total(void *data)
{
    vector_t *vector = (vector_t *)(data - sizeof(vector_t));

    return vector->current;
}
