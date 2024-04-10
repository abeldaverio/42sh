/*
** EPITECH PROJECT, 2024
** clear special
** File description:
** handles the case where specials are sticking to another char
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "special_strings.h"
#include "env.h"

static bool is_there_special_str(char *input, char const *special)
{
    for (int i = 0; special[i] != '\0'; i++) {
        if (input[i] != special[i])
            return false;
        if (input[i] == '\0')
            return false;
    }
    return true;
}

static void check_special_str(int *i, char *input, int *count)
{
    for (int j = 0; j < SPECIAL_SIZE; j++) {
        if (input[*i] == '\\' && input[*i + 1] != '\0')
            *i += 1;
        if (is_there_special_str(input + *i, SPECIAL[j])) {
            *i += strlen(SPECIAL[j]) - 1;
            *count += 2;
            return;
        }
    }
}

static size_t new_stinrg_len(char *input)
{
    int count = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        check_special_str(&i, input, &count);
    }
    return (strlen(input) + count);
}

static void fill_new_string_special(char *new, char const *special)
{
    for (int i = 0; special[i] != '\0'; i++) {
        new[i] = special[i];
    }
}

static bool fill_special(char *input, char *new, int *i, int *j)
{
    for (int z = 0; z < SPECIAL_SIZE; z++) {
        if (is_there_special_str(input, SPECIAL[z])) {
            new[*j] = ' ';
            *j += 1;
            fill_new_string_special(new + *j, SPECIAL[z]);
            *j += strlen(SPECIAL[z]);
            new[*j] = ' ';
            *j += 1;
            *i += strlen(SPECIAL[z]);
            return true;
        }
    }
    return false;
}

static void fill_new_string(char *input, char *new)
{
    int i = 0;
    int j = 0;

    while (input[i] != '\0') {
        if (fill_special(input + i, new, &i, &j))
            continue;
        new[j] = input[i];
        i++;
        j++;
    }
    new[j] = '\0';
}

char *clear_special(char *input)
{
    int len = new_stinrg_len(input);
    char *new = calloc(sizeof(char), (len + 1));

    if (new == NULL)
        exit(84);
    fill_new_string(input, new);
    return new;
}
