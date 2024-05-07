/*
** EPITECH PROJECT, 2024
** prompt.h
** File description:
** prompt header
*/

#ifndef PROMPT_H
    #define PROMPT_H

    #include <stddef.h>
    #include <stdio.h>

typedef struct prompt_s {
    char character;
    ssize_t index;
    char **line;
    size_t prompt_size;
    int tty;
} prompt_t;

#endif /* PROMPT_H */
