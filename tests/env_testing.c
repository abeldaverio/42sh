/*
** EPITECH PROJECT, 2024
** unit tests
** File description:
** env testing
*/

#include "env.h"
#include "functions.h"
#include "header_test.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

Test(init_env_test, env_testing)
{
    char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert_not_null(env_s);
    cr_assert_not_null(env_s->aliases);
    cr_assert_not_null(env_s->env_list);
    cr_assert_not_null(env_s->old_pwd);
    cr_assert_not_null(env_s->shell_variables);
    cr_assert_not_null(env_s->history);
    char **env_arr = get_env_array(env_s->env_list);
    cr_assert_not_null(env_arr);
    free_array(env_arr);
    free_env(env_s);
}

Test(linked_list_env_test, env_testing)
{
    char *env[] = {
        "DISPLAY=1",
        "PATH=/usr/bin",
        "USER=TEST",
        "VARTEST=1",
        "VAR=1",
        NULL
    };
    env_t *env_s = init_env((const char **) env);

    cr_assert_not_null(env_s);

    char **disp_value = get_formated_value("DISPLAY", env_s->env_list);
    cr_assert_not_null(env_s);
    cr_assert_str_eq(disp_value[0], "1");
    free_array(disp_value);
    free_env(env_s);
}
