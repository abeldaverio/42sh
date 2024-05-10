/*
** EPITECH PROJECT, 2023
** redirect
** File description:
** redirects the output for tests purposes
*/

#include "functions.h"
#include "header_test.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <stdlib.h>
#include "macros.h"
#include "vector.h"

/*
** TEMPLATES:

Test(TEST_NAME, TEST_SECTION)
{
    cr_assert_eq(1, 1);
}

Test(TEST_NAME, TEST_SECTION, .init = redirect_all_std)
{
    //your prints
    cr_assert_stdout_eq_str("WHATEVER");
*/

Test(vector_free_null, vector)
{
    vector_free(NULL);
}

Test(vector_free_malloc, vector)
{
    char *data = vector_init(sizeof(char));

    vector_free(data);
}

Test(check_free_null, vector)
{
    check_free(NULL);
}

Test(check_free_malloc, vector)
{
    char *data = malloc(sizeof(char) * 3);

    check_free(data);
}

Test(vector_add_null, vector)
{
    vector_add(NULL, NULL);
}

Test(vector_add_vector_null, vector)
{
    char c = '\0';

    vector_add(NULL, &c);
}

Test(vector_add_char_null, vector)
{
    char *data = vector_init(sizeof(char));

    vector_add(&data, NULL);
    vector_free(data);
}

Test(vector_add_normal, vector)
{
    char *data = vector_init(sizeof(char));
    char c = '\0';

    vector_add(&data, &c);
    vector_free(data);
}

Test(vector_add_resize, vector)
{
    char *data = vector_init(sizeof(char));
    char c = '\0';

    for (size_t i = 0; i < 6; ++i)
        vector_add(&data, &c);
    vector_free(data);
}

Test(str_to_vector_null, vector)
{
    str_to_vector(NULL);
}

Test(vector_to_str_null, vector)
{
    vector_to_str(NULL);
}
