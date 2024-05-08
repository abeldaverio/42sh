/*
** EPITECH PROJECT, 2024
** print line
** File description:
** input
*/

#include <stdbool.h>
#include "prompt.h"
#include "env.h"
#include "arrows.h"
#include "functions.h"
#include "vector.h"

void print_input_line(prompt_t *prompt, env_t *env, bool del)
{
    cursor_backward(prompt->prompt_size + prompt->index);
    dprintf(1, "\33[K");
    print_prompt(env, prompt->tty);
    dprintf(1, "%.*s", (int)vector_total(*prompt->line), *prompt->line);
    cursor_backward(vector_total(*prompt->line));
    if (vector_total(*prompt->line) == 0)
        prompt->index += 1;
    if (del)
        cursor_forward(prompt->index == 1 ? prompt->index - 1 : prompt->index);
    else
        cursor_forward(prompt->index + 1);
    if (vector_total(*prompt->line) == 0)
        prompt->index -= 1;
}
