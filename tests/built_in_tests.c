/*
** EPITECH PROJECT, 2024
** built_in_test
** File description:
** test
*/

#include "functions.h"
#include "header_test.h"
#include "possibility.h"
#include "built_in.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include "macros.h"

Test(exit_test_success, test1)
{
    char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "exit",
        "43",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert_not_null(env_s);

    cr_assert_not(set_exit_value((char **)args, env_s));
    cr_assert_eq(env_s->last_return, 43);
}

Test(exit_test_failure, test2, .init=redirect_all_std)
{
    char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "exit",
        "prout",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert_not_null(env_s);

    cr_assert(set_exit_value((char **)args, env_s));
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(env_s->last_return, 1);
}

Test(append_to_variable_test, test3)
{
    char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "DISPLAY+=caca",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert_not_null(env_s);

    append_to_variable((char **)args, env_s);
    char *test = search_env_value("DISPLAY", env_s->env_list);
    cr_assert_str_eq(test, "1caca");
}

Test(set_variable_test, test4)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "prout=caca",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    set_variable(args, env_s);
    char *test = search_env_value("prout", env_s->shell_variables);
    cr_assert_str_eq("caca", test);
}

Test(set_variable_env_test, test4)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "DISPLAY=caca",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    set_variable(args, env_s);
    char *test = search_env_value("DISPLAY", env_s->env_list);
    cr_assert_str_eq("caca", test);
}

Test(test_fetch, test5, .init=redirect_all_std)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "camillefetch",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert(camille_fetch(args, env_s));
    cr_assert_eq(env_s->last_return, 0);
}

Test(test_alias_set, test6)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "alias",
        "a=echo a",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert(set_alias(args, env_s));
    cr_assert_eq(env_s->last_return, 0);
    char *test = search_env_value("a", env_s->aliases);
    cr_assert_str_eq(test, "echo a");
}

Test(test_set_env, test7)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "setenv",
        "HIHI",
        "HOHO",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert(set_env(args, env_s));
    cr_assert_eq(env_s->last_return, 0);
    char *test = search_env_value("HIHI", env_s->env_list);
    cr_assert_str_eq(test, "HOHO");
}


Test(test_unset_env, test7)
{
        char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    char *args[] = {
        "unsetenv",
        "DISPLAY",
        NULL,
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert(unset_env(args, env_s));
    cr_assert_eq(env_s->last_return, 0);
    char *test = search_env_value("DISPLAY", env_s->env_list);
    cr_assert_null(test);
}