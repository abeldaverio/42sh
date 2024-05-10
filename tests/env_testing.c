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
    cr_assert_not_null(disp_value);
    cr_assert_str_eq(disp_value[0], "1");
    free_array(disp_value);

    insert_int_in_env("TEST", 69, env_s->env_list);
    char *insert_test = search_env_value("TEST", env_s->env_list);
    cr_assert_not_null(insert_test);
    cr_assert_str_eq(insert_test, "69");

    insert_int_in_env("TEST", 420, env_s->env_list);
    char *reinsert_test = search_env_value("TEST", env_s->env_list);
    cr_assert_not_null(reinsert_test);
    cr_assert_str_eq(reinsert_test, "420");
    free_env(env_s);
}

Test(prompt_boring_test, prompt, .init=redirect_all_std)
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

    insert_in_env("HOST", "fedora", env_s->env_list);
    insert_in_env("USER", "abeldaverio", env_s->env_list);
    insert_in_env("PWD", "caca/B-PSU-200-PAR-2-1-42sh-luc.simon", env_s->env_list);
    remove_from_env("PROMPT_COLORS", env_s->env_list);
    print_prompt(env_s, 1);
    cr_assert_stdout_eq_str("abeldaverio@fedora:B-PSU-200-PAR-2-1-42sh-luc.simon > 0 $> ");
}

Test(prompt_cool_test, prompt, .init=redirect_all_std)
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

    insert_in_env("HOST", "fedora", env_s->env_list);
    insert_in_env("USER", "abeldaverio", env_s->env_list);
    insert_in_env("PWD", "caca/B-PSU-200-PAR-2-1-42sh-luc.simon", env_s->env_list);
    insert_in_env("PROMPT_COLORS", "", env_s->env_list);
    print_prompt(env_s, 1);
    cr_assert_stdout_eq_str("abeldaverio\033[0m@fedora\033[0m:B-PSU-200-PAR-2-1-42sh-luc.simon\033[0m > 0\033[0m $> \033[0m");
}