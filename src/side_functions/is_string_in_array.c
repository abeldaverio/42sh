/*
** EPITECH PROJECT, 2024
** is string in array
** File description:
** check if string is in array
*/

#include <string.h>
#include <stdbool.h>

bool is_string_in_array(char const *const str, char const *const *const array)
{
    for (int i = 0; array[i]; ++i) {
        if (strcmp(array[i], str) == 0)
            return true;
    }
    return false;
}
