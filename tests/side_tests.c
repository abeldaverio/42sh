/*
** EPITECH PROJECT, 2024
** test on side functions
** File description:
** tests
*/

#include "header_test.h"
#include "functions.h"

Test(int_to_str_positive_test, test1)
{
    int i = 3;
    char *str = int_to_str(i);

    cr_assert_str_eq(str, "3");
}

Test(int_to_str_negative_test, test2)
{
    int i = -32;
    char *str = int_to_str(i);

    cr_assert_str_eq(str, "-32");
}

Test(is_string_in_array_success, test3)
{
    char *array[] = {
        "VEVEFRANCE",
        "cacafire",
        "cacaview",
        "la maturité on connais hein",
        "prout",
    };

    cr_assert(is_string_in_array("cacafire", (char const *const *)array));
}

Test(is_string_in_array_failure, test4)
{
    char *array[] = {
        "VEVEFRANCE",
        "cacafire",
        "cacaview",
        "la maturité on connais hein",
        "prout",
    };

    cr_assert_not(is_string_in_array("cacademo", (char const *const *)array));
}

Test(my_arraydup_test, test5)
{
    char *array[] = {
        "VEVEFRANCE",
        "cacafire",
        "cacaview",
        "la maturité on connais hein",
        "prout",
        NULL,
    };
    char **test = my_arraydup((const char *const *const)array);

    assert_char_arrays(array, test);
    free_array(test);
}

Test(my_arralen_test, test6)
{
    char *array[] = {
        "VEVEFRANCE",
        "cacafire",
        "cacaview",
        "la maturité on connais hein",
        "prout",
        NULL,
    };

    cr_assert_eq(my_arraylen((char const *const *const)array), 5);
}

Test(my_strcat_classic_test, test6)
{
    char first[] = "first";
    char second[] = "second";
    char *test = my_strcat(2, first, second);

    cr_assert_str_eq("firstsecond", test);
    free(test);
}

Test(my_strcat_NULL_test, test6)
{
    char first[] = "first";
    char *test = my_strcat(2, NULL, first);

    cr_assert_str_eq("first", test);
    free(test);
}
