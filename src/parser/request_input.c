/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** just a func to request input
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static char *get_input(void)
{
    ssize_t input_size = 0;
    size_t temp = 0;
    char *input = NULL;

    while (input_size == 0) {
        input_size = getline(&input, &temp, stdin);
        if (input_size == -1 && input != NULL)
            free(input);
        if (input_size == -1) {
            return NULL;
        }
    }
    return input;
}

void request_input(char **input, char const *img)
{
    if (*input != NULL)
        free(*input);
    if (isatty(0))
        dprintf(1, "%s", img);
    *input = get_input();
}
