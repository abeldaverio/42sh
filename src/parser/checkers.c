/*
** EPITECH PROJECT, 2024
** array lib
** File description:
** checkers for strings
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool ischar_in_str(char c, const char *separators)
{
    if (separators == NULL)
        return 0;
    for (int i = 0; separators[i]; i++)
        if (c == separators[i])
            return 1;
    return 0;
}

bool str_contains(const char *str, const char *tocheck)
{
    for (int i = 0; str[i]; i++) {
        if (!ischar_in_str(str[i], tocheck))
            return 0;
    }
    return 1;
}

int str_in_tab(char const *const *tab, char const *str)
{
    int tot = 0;

    if (tab == NULL)
        return 0;
    for (uint i = 0; tab[i] != NULL; i++) {
        if (strcmp(tab[i], str))
            tot += 1;
    }
    return tot;
}

bool find_char_str(char const *str, char const *to_check)
{
    for (int i = 0; str[i]; i++) {
        if (ischar_in_str(str[i], to_check))
            return i;
    }
    return -1;
}
