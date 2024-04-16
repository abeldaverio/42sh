/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** star formating
*/

#include "functions.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static size_t get_suffix_size(char *input, int star_pos)
{
    int counter = 0;

    for (int i = star_pos - 1; i >= 0 &&
        input[i] != '\"' && input[i] != ' '; i--) {
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
    for (int i = star_pos - 1; i >= 0 &&
        input[i] != '\"' && input[i] != ' '; i--) {
        star_suffix[counter] = input[i];
        counter--;
    }
    return star_suffix;
}

static size_t get_prefix_size(char *input, int star_pos)
{
    int counter = 0;

    for (int i = star_pos + 1; input[i] &&
        input[i] != '\"' && input[i] != ' '; i++) {
        counter++;
    }
    return counter;
}

static char *get_prefix(char *input, int star_pos)
{
    int counter = get_prefix_size(input, star_pos) - 1;
    char *star_prefix = calloc(sizeof(char), counter + 1);

    if (star_prefix == NULL)
        return NULL;
    for (int i = star_pos + 1; input[i] &&
        input[i] != '\"' && input[i] != ' '; i++) {
        star_prefix[counter] = input[i];
        counter++;
    }
    return star_prefix;
}

static char **tab_reconstructor(char **input, char **options, int to_replace)
{
    char **new_tab = NULL;

    new_tab = calloc(my_arraylen(input) +
        my_arraylen(options) - 1, sizeof(char *));
    for (int i = 0; input[i] != NULL; i++) {
        if (i != to_replace)
            new_tab[i] = strdup(input[i]);
        for (int y = 0; i == to_replace && options[y]; y++) {
            new_tab[i + y] = strdup(options[y]);
        }
    }
    return new_tab;
}

static char **star_replacing(char **input, int to_replace)
{
    char *star_prefix = NULL;
    char *star_suffix = NULL;
    char **options = NULL;
    char *temp = NULL;

    for (int i = 0; input[to_replace][i]; i++) {
        if (input[to_replace][i] == '*') {
            star_suffix = get_suffix(input[to_replace], i);
            star_prefix = get_prefix(input[to_replace], i);
            break;
        }
    }
    options = open_config_dir(star_suffix);
    for (int i = 0; options[i] != NULL; i++) {
        temp = options[i];
        options[i] = my_strcat(3, star_suffix, options[i], star_prefix);
        free(temp);
    }
    return tab_reconstructor(input, options, to_replace);
}

bool format_input(char ***input)
{
    char **temp = *input;
    char **to_free = NULL;

    for (int i = 1; temp[i] != NULL; i++) {
        if (strcmp(temp[i], "*") == 0 ||
            strstr(temp[i], "*") != temp[i]) {
            to_free = *input;
            *input = star_replacing(temp, i);
            free_array(to_free);
        }
    }
    return false;
}
