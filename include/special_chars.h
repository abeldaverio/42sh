/*
** EPITECH PROJECT, 2024
** special chars
** File description:
** terminos special chars
*/

#pragma once

    #include "macros.h"
    #include "prompt.h"
    #include "env.h"

typedef struct special_chars_s {
    char character;
    int (*function)(prompt_t *, env_t *);
}special_chars_t;

int delete_command(prompt_t *, env_t *);
int arrow_handle(prompt_t *, env_t *);
int handle_exit(prompt_t *, env_t *);

static const special_chars_t SPECIAL_INPUT[] = {
    {END_OF_FILE, handle_exit},
    {'\0', handle_exit},
    {'\033', arrow_handle},
    {KEY_DEL, delete_command},
};

static const size_t NB_OF_SPECIAL_INPUT =
sizeof(SPECIAL_INPUT) / sizeof(special_chars_t);
