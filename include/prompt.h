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
    #include <stdbool.h>

typedef struct prompt_s {
    char character;
    ssize_t index;
    char **line;
    size_t prompt_size;
    int tty;
    char *completion_candidate;
    bool in_completion;
    int completion_ptr;
    int last_completion_offset;
} prompt_t;

#endif /* PROMPT_H */
