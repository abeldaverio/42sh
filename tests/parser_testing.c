/*
** EPITECH PROJECT, 2024
** unit tests
** File description:
** parser testing
*/

#include "complete.h"
#include "header_test.h"
#include "ll_parsing.h"
#include "vector.h"
#include "functions.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>

Test(parser_basic, parser_func, .init=redirect_all_std)
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
    cr_assert_neq(start_tree(env_s, "ls"), true);
    free_env(env_s);
    return;
}

Test(parser_advanced, parser_func)
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
    cr_assert_neq(start_tree(env_s, "ls | cat -e > file; ls | cat -e >> file"), true);
    free_env(env_s);
    return;
}

Test(parser_alone, parser_unit)
{
    ll_node_t *node = ll_parser("ls");

    cr_assert_not_null(node);
    cr_assert_eq(node->is_operator, false);
    cr_assert_str_eq(node->value, "ls");
    cr_assert_null(node->left);
    cr_assert_null(node->right);
    free_tree(node);
    return;
}

Test(parser_alone_advanced, parser_unit)
{
    ll_node_t *node = ll_parser("ls\1|\1cat -e");

    cr_assert_not_null(node);
    cr_assert_eq(node->is_operator, true);
    cr_assert_str_eq(node->value, "|");
    cr_assert_not_null(node->right);
    cr_assert_not_null(node->left);

    cr_assert_eq(node->left->is_operator, false);
    cr_assert_str_eq(node->left->value, "ls");
    cr_assert_null(node->left->right);
    cr_assert_null(node->left->left);

    cr_assert_eq(node->right->is_operator, false);
    cr_assert_str_eq(node->right->value, "cat -e");
    cr_assert_null(node->right->right);
    cr_assert_null(node->right->left);

    free_tree(node);
    return;
}

Test(parser_alone_error, parser_unit)
{
    ll_node_t *node = ll_parser(NULL);

    cr_assert_null(node);
    return;
}
