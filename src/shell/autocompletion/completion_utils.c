/*
** EPITECH PROJECT, 2024
** 42 sh
** File description:
** completion utils
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "complete.h"
#include "functions.h"
#include "vector.h"
#include "macros.h"

static char *alloc_completion(char *input, int *counter_ptr, bool stop_at_dir)
{
    char *new_str = NULL;
    int counter = 0;

    for (int i = vector_total(input) - 1; i >= 0; i--) {
        if (stop_at_dir && input[i] == '/')
            break;
        if (input[i] == ' ' || input[i] == '\0' || input[i] == '\t') {
            break;
        }
        counter++;
    }
    if (counter <= 0)
        return NULL;
    new_str = calloc(counter + 1, sizeof(char));
    *counter_ptr = counter;
    return new_str;
}

char *get_completion(char *input, bool stop_at_dir)
{
    int counter = 0;
    char *new_str = alloc_completion(input, &counter, stop_at_dir);
    int counter_dup = 0;

    if (new_str == NULL)
        return NULL;
    counter -= 1;
    for (int i = counter; i >= 0; i--) {
        new_str[i] = input[(vector_total(input) - 1) - counter_dup];
        counter_dup++;
    }
    return new_str;
}

char *isolate_completion(char **candidates, int completion_ptr)
{
    char *full_glob = candidates[completion_ptr];
    char **formated_glob = format_arguments(full_glob, "/", "");
    char *final_str = NULL;

    if (formated_glob == NULL)
        return NULL;
    final_str = strdup(formated_glob[my_arraylen(CONST_A(formated_glob)) - 1]);
    free_array(formated_glob);
    return final_str;
}
