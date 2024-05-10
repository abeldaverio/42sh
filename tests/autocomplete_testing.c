/*
** EPITECH PROJECT, 2024
** unit tests
** File description:
** autocompletion tests
*/

#include "complete.h"
#include "header_test.h"
#include "vector.h"
#include "functions.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

Test(auto_complete_basic_dir, auto_complet_func)
{
    char *input = str_to_vector("git include/");
    char *completion = get_completion_result(input, 1);

    cr_assert_not_null(completion);
    free(completion);
    vector_free(input);
}

Test(auto_complete_basic_cmd, auto_complet_func)
{
    char *input = str_to_vector("gi");
    char *completion = get_completion_result(input, 1);

    cr_assert_not_null(completion);
    free(completion);
    vector_free(input);
}

Test(auto_complete_null, auto_complet_func)
{
    char *input = str_to_vector("");
    char *completion = get_completion_result(input, 0);

    cr_assert_not_null(completion);
    free(completion);
    vector_free(input);
}

Test(auto_complete_print_cmd, auto_complet_func)
{
    char *input = str_to_vector("gi");
    int info[3] = {0};
    int *lineinf = auto_complete(input, 0, info);

    cr_assert_not_null(lineinf);
    cr_assert_neq(info[WORDS_INFO], 0);
    cr_assert_neq(info[CHARS_INFO], 0);
    free(lineinf);
    vector_free(input);
}

Test(auto_complete_print_dir, auto_complet_func)
{
    char *input = str_to_vector("git include/");
    int info[3] = {0};
    int *lineinf = auto_complete(input, 0, info);

    cr_assert_not_null(lineinf);
    cr_assert_neq(info[WORDS_INFO], 0);
    cr_assert_neq(info[CHARS_INFO], 0);
    free(lineinf);
    vector_free(input);
}
