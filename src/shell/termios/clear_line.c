/*
** EPITECH PROJECT, 2024
** clear line
** File description:
** ctrl C
*/

#include <stddef.h>
#include "prompt.h"
#include "functions.h"
#include "vector.h"

int clear_line(prompt_t *prompt, env_t *env)
{
    dprintf(1, "\n");
    vector_free(*prompt->line);
    *prompt->line = vector_init(sizeof(char));
    if (*prompt->line == NULL)
        return -1;
    prompt->index = 0;
    print_input_line(prompt, env, true);
    return prompt->index;
}