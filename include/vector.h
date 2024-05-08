/*
** EPITECH PROJECT, 2024
** vector.h
** File description:
** vector header
*/

#ifndef VECTOR_H
    #define VECTOR_H

    #include <stddef.h>

typedef struct vector_s {
    size_t current;
    size_t max;
    size_t size;
} vector_t;

static size_t const VECTOR_INIT_SIZE = 5;

void *vector_init(size_t size_of);
size_t vector_total(void *);
void vector_resize(vector_t **vector, size_t new);
void vector_add(void *data, void *c);
void vector_set(void *data, size_t index, void *item);
void vector_delete(void *data, size_t index);
void vector_free(void *data);
void vector_push(void *data, size_t index, void *c);
void check_free(void *ptr);
void vector_normal(void *data, void *c);

#endif

/* *(int *) &vector[i * sizeof(int)]; */
