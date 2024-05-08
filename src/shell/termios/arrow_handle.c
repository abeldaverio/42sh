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

size_t arrow_handle(prompt_t *prompt)
{
    char c = getchar();

    if (c != '[')
        return prompt->index;
    c = getchar();
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
