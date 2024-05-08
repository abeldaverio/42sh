/*
** EPITECH PROJECT, 2024
** arrows
** File description:
** functions for arrows key
*/

#pragma once

    #include <stddef.h>
    #include "prompt.h"
    #include "env.h"

typedef struct arrows_s {
    char character;
    void (*function)(prompt_t *, env_t *);
}arrows_t;

void cursor_backward(size_t i);
void cursor_forward(size_t i);

void up_arrow_command(prompt_t *, env_t *);
void down_arrow_command(prompt_t *, env_t *);
void right_arrow_command(prompt_t *, env_t *);
void left_arrow_command(prompt_t *, env_t *);

static const arrows_t ARROWS_COMMAND[] = {
    {'A', up_arrow_command},
    {'B', down_arrow_command},
    {'C', right_arrow_command},
    {'D', left_arrow_command},
};

static const size_t NB_OF_ARROWS =
sizeof(ARROWS_COMMAND) / sizeof(arrows_t);
