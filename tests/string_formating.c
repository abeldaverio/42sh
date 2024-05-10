/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** string_formating
*/

#include "header_test.h"
#include "functions.h"

Test(First, my_array_concat)
{
    char *first[] = {"HELLO",
                    NULL};
    char *second[] = {"WORLD",
                    NULL};
    char *res[] = {"HELLO", "WORLD", NULL};

    cr_assert_arr_eq(res, array_concat(first, second), 0);
}
