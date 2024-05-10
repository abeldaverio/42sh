/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** star formating
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <unistd.h>
#include "macros.h"
#include "functions.h"

static char **tab_reconstructor(char **input, char **options, int to_replace)
{
    char **new_tab = NULL;
    int offset = 0;

    new_tab = calloc(my_arraylen(CONST_A(input)) +
        my_arraylen(CONST_A(options)), sizeof(char *));
    if (new_tab == NULL)
        return NULL;
    for (int i = 0; input[i] != NULL; i++) {
        if (i != to_replace)
            new_tab[i + offset] = strdup(input[i]);
        for (int y = 0; i == to_replace && options[y]; y++) {
            new_tab[i + y] = strdup(options[y]);
            offset = y;
        }
    }
    return new_tab;
}

static char **star_replacing(char **input,
    int to_replace, int *offset, bool *error)
{
    glob_t globbuf;
    char **new_tab = NULL;

    globbuf.gl_offs = 0;
    if (glob(input[to_replace], GLOB_DOOFFS, NULL, &globbuf)) {
        dprintf(STDERR_FILENO, "Error : %s, expression not found\n",
        input[to_replace]);
        *error = true;
        globfree(&globbuf);
        return NULL;
    }
    *offset = my_arraylen(CONST_A(globbuf.gl_pathv)) - 1;
    new_tab = tab_reconstructor(input, globbuf.gl_pathv, to_replace);
    globfree(&globbuf);
    return new_tab;
}

static bool star_checking(char *candidate)
{
    char *star_ptr = strstr(candidate, "*");

    if (star_ptr == NULL)
        return false;
    if (strlen(candidate) != strlen(star_ptr))
        if (star_ptr[-1] == '\\')
            return false;
    return true;
}

static bool star_exec(char **tab_dup, int i, char ***input, int *to_offset)
{
    char **temp = NULL;
    char **to_free = NULL;
    bool error = false;

    if (star_checking(tab_dup[i]))
        temp = star_replacing(*input, i + *to_offset, to_offset, &error);
    if (error) {
        return true;
    }
    if (temp != NULL) {
        to_free = *input;
        *input = temp;
        free_array(to_free);
    }
    return false;
}

bool format_input(char ***input)
{
    char **tab_dup = my_arraydup(CONST_A(*input));
    int to_offset = 0;

    for (int i = 0; tab_dup[i] != NULL; i++) {
        if (star_exec(tab_dup, i, input, &to_offset)) {
            free_array(tab_dup);
            return true;
        }
    }
    free_array(tab_dup);
    return false;
}
