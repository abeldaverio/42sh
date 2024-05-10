/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_left
*/

#include <stddef.h>
#include <stdio.h>
#include "env.h"
#include "functions.h"
#include "prompt.h"
#include "special_chars.h"

void cursor_backward(size_t i)
{
    dprintf(1, "\033[%ldD", i);
}

void left_arrow_command(prompt_t *prompt, env_t *env)
{
    if (prompt->in_completion) {
        handle_tab_completion(prompt, env, -1);
        return;
    }
    if (prompt->index > 0) {
        cursor_backward(1);
        prompt->index -= 1;
    }
}
