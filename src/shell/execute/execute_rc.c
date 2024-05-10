/*
** EPITECH PROJECT, 2024
** execute rc
** File description:
** execute the rc file
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "env.h"
#include "macros.h"
#include "functions.h"

void execute_rc(env_t *env)
{
    size_t tmp = 0;
    char *input = NULL;
    char *new_input = NULL;
    FILE *file = fopen(RC_FILE, "r");

    if (file == NULL)
        return;
    while ((getline(&input, &tmp, file) != -1)) {
        new_input = clear_special(input);
        if (handle_input(new_input, env))
            break;
    }
    fclose(file);
    if (input != NULL)
        free(input);
}
