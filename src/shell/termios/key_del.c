/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_del
*/

#include <stdbool.h>
#include <stdio.h>
#include "macros.h"
#include "vector.h"
#include "prompt.h"
#include "functions.h"

size_t delete_command(prompt_t *prompt, env_t *env)
{
    if (prompt->index <= 0)
        return prompt->index;
    vector_delete(prompt->line, prompt->index - 1);
    if (prompt->index > 1)
        prompt->index -= 1;
    else
        prompt->index -= 2;
    print_input_line(prompt, env, true);
    if (prompt->index <= 0)
        prompt->index += 1;
    return prompt->index;
}
