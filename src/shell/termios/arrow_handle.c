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

int arrow_handle(prompt_t *prompt, env_t *env)
{
    char c = my_getchar();

    if (c != '[')
        return prompt->index;
    c = my_getchar();
    for (size_t i = 0; i < NB_OF_ARROWS; ++i) {
        if (c == ARROWS_COMMAND[i].character) {
            ARROWS_COMMAND[i].function(prompt, env);
            break;
        }
    }
    return prompt->index;
}
