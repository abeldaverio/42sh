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

Test(Second, clear_special)
{
    char input[] = {'L',
                    'O',
                    'L',
                    '>',
                    '\0'};
    char res[] = {'L',
                'O',
                'L',
                '\1',
                '>',
                '\1',
                '\0'};
    cr_assert_str_eq(res, clear_special(input), "LOSE");
}

Test(third, format_input)
{
    char input[] = "WOW WORKING?";
    char *test[] = {
        "WOW",
        "WORKING?",
        NULL,
    };
    char **input_twod = format_arguments(input, " \t\n", "\"\'");

    assert_char_arrays(test, input_twod);
}

Test(fourth, display_env)
{
    char *argv[] = {"print", "env", NULL};
    env_t *env = malloc(sizeof(*env));
    
    cr_assert_eq(true, display_env(argv, env), "NOPE");
}

Test(fifth, display_env)
{
    char *argv[] = {"env", NULL};
    env_t *env = malloc(sizeof(*env));

    env->env_list = malloc(sizeof(env_list_t *));
    cr_assert_eq(true, display_env(argv, env), "NOPE");
}

void fill_env_list(env_list_t **env)
{
    char value[] = {'V',
                    'A',
                    'L',
                    '\0'};
    char variable[] = {'V',
                        'A',
                        'R',
                        '\0'};
    (*env) = malloc(sizeof(env_list_t *));
    (*env)->value = strdup(value);
    (*env)->variable = strdup(variable);
    (*env)->next = NULL;
}

Test(sixth, display_env)
{
    char *argv[] = {"env", NULL};
    env_t *env = malloc(sizeof(*env));

    env->env_list = malloc(sizeof(env_list_t **));
    fill_env_list(env->env_list);
    cr_assert_eq(true, display_env(argv, env), "NOPE");
    free((*env->env_list));
    free(env->env_list);
    free(env);
}

Test(basic_star, star_test)
{
    char **input = format_arguments("ls src/*", " ", "");

    cr_assert_eq(format_input(&input), false);
    free_array(input);
}
