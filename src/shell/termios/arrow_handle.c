/*
** EPITECH PROJECT, 2024
** arrow handle
** File description:
** arrow handle terminos
*/

#include <stddef.h>
#include "prompt.h"
#include "vector.h"
#include "arrows.h"
#include "functions.h"

int arrow_handle(prompt_t *prompt, env_t *)
{
    char c = my_getchar();

    if (c != '[')
        return prompt->index;
    c = my_getchar();
    if (c == 'D' && prompt->index > 0) {
        cursor_backward(1);
        prompt->index -= 1;
    }
    if (c == 'C' && prompt->index < (ssize_t)vector_total(*prompt->line)) {
        cursor_forward(1);
        prompt->index += 1;
    }
    return prompt->index;
}
