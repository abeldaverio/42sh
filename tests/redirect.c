/*
** EPITECH PROJECT, 2023
** redirect
** File description:
** redirects the output for tests purposes
*/

#include "header_test.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

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
