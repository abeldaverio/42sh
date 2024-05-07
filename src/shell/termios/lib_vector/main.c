/*
** EPITECH PROJECT, 2024
** main
** File description:
** main
*/

#include "vector.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char *data = vector_init(sizeof(char));
    char c = 'f';

    vector_add(&data, &c);
    c = 'o';
    vector_add(&data, &c);
    c = 'o';
    vector_add(&data, &c);
    c = ' ';
    vector_add(&data, &c);
    c = 'b';
    vector_add(&data, &c);
    c = 'a';
    vector_add(&data, &c);
    c = 'r';
    vector_add(&data, &c);
    c = ' ';
    vector_add(&data, &c);
    c = 'f';
    vector_add(&data, &c);
    c = 'o';
    vector_add(&data, &c);
    c = 'o';
    vector_add(&data, &c);
    vector_delete(&data, 3);
    vector_delete(&data, 0);
    vector_delete(&data, 9);
    c = '?';
    vector_set(&data, 0, &c);
    write(1, data, vector_total(data));
    write(1 , "\n", 1);
    vector_free(data);
    return (0);
}
