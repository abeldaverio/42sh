/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** star formating
*/

#include "functions.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static char *get_prefix(char *input, int star_pos)
{
    char *star_prefix = calloc(sizeof(char), 1);;
    int counter = 0;

    if (star_prefix == NULL)
        return NULL;
    for (int i = star_pos; input[i] && input[i] != '\"' && input[i] != ' '; i++) {
        star_prefix = reallocarray(star_prefix, strlen(star_prefix) + 1, sizeof(char));
        star_prefix[counter] = input[i];

    }
    return star_prefix;
}

static size_t get_suffix_size(char *input, int star_pos)
{
    char *star_suffix = calloc(sizeof(char), 1);
    int counter = 0;

    if (star_suffix == NULL)
        return 0;
    for (int i = star_pos - 1; i >= 0 && input[i] != '\"' && input[i] != ' '; i--) {
        counter++;
    }
    return counter;
}

static char *get_suffix(char *input, int star_pos)
{
    int counter = get_suffix_size(input, star_pos) - 1;
    char *star_suffix = calloc(sizeof(char), counter + 1);

    if (star_suffix == NULL)
        return NULL;
    for (int i = star_pos - 1; i >= 0 && input[i] != '\"' && input[i] != ' '; i--) {
        star_suffix[counter] = input[i];
        counter--;
    }
    return star_suffix;
}

static char *star_replacing(char *input, int star_pos)
{
    char *star_prefix = NULL;
    char *star_suffix = NULL;
    char *new_string = NULL;
    char **options = NULL;

    star_suffix = get_suffix(input, star_pos);
    star_prefix = get_prefix(input, star_pos);
    options = open_config_dir(star_suffix);
    for (int i = 0; options[i] != NULL; i++) {
        new_string = my_strcat(4, new_string, star_suffix, options[i], " ");
    }
    return new_string;
}

char *format_input(char *input)
{
    char *new_input = NULL;
    char *temp_input = NULL;

    if (strstr(input, "*") == input)
        return input;
    for (int i = 0; input[i]; i++) {
        if (input[i] == '*') {
            temp_input = star_replacing(input, i);
        }
    }
    return new_input;
}
