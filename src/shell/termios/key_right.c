/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_right
*/

#include <stddef.h>
#include <stdio.h>
#include "vector.h"
#include "env.h"
#include "prompt.h"
#include "special_chars.h"

void cursor_forward(size_t i)
{
    dprintf(1, "\033[%ldC", i);
}

void right_arrow_command(prompt_t *prompt, env_t *env)
{
    if (prompt->in_completion) {
        handle_tab_completion(prompt, env, 1);
        return;
    }
    if (prompt->index < (ssize_t)vector_total(*prompt->line)) {
        cursor_forward(1);
        prompt->index += 1;
    }
}
