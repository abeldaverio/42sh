/*
** EPITECH PROJECT, 2024
** possibility testing
** File description:
** test
*/

#include "functions.h"
#include "header_test.h"
#include "possibility.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

Test(test_append_success, test1, .init=redirect_all_std)
{
    char *args[] = {
        "a+=1",
        NULL
    };
    cr_assert(is_it_append_variable(args));
    return;
}

Test(test_append_fail, test2, .init=redirect_all_std)
{
    char *args[] = {
        "a=1",
        NULL
    };
    cr_assert_not(is_it_append_variable(args));
    return;
}

Test(test_set_success, test3, .init=redirect_all_std)
{
    char *args[] = {
        "a=1",
        NULL
    };
    cr_assert(is_it_variable(args));
    return;
}

Test(test_set_failure, test4, .init=redirect_all_std)
{
    char *args[] = {
        "LHGLKJDSHGLS",
        NULL
    };
    cr_assert_not(is_it_variable(args));
    return;
}

Test(test_command_success, test5, .init=redirect_all_std)
{
    char *args[] = {
        "prout",
        NULL
    };
    cr_assert(is_it_command(args));
    return;
}

Test(test_command_failure, test6, .init=redirect_all_std)
{
    char *args[] = {
        "./prout",
        NULL
    };
    cr_assert_not(is_it_command(args));
    return;
}


