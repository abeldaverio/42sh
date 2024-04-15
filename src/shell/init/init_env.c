/*
** EPITECH PROJECT, 2024
** init env
** File description:
** init env
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "env.h"
#include "functions.h"

static int get_variable_size(char const *line)
{
    int i;

    for (i = 0; line[i] != '=' && line[i] != '\0'; i++);
    return i;
}

char **separate_line(char const *line)
{
    char **tmp = calloc(sizeof(char *), 3);
    int variable_size = get_variable_size(line);

    if (tmp == NULL)
        return NULL;
    tmp[0] = calloc(sizeof(char), variable_size + 1);
    if (tmp[0] == NULL)
        return NULL;
    for (int i = 0; i < variable_size; i++) {
        tmp[0][i] = line[i];
    }
    tmp[0][variable_size] = '\0';
    tmp[1] = strdup(line + variable_size + 1);
    if (tmp[1] == NULL)
        return NULL;
    return tmp;
}

static bool fill_the_list(env_list_t **env, char const **env_array)
{
    char **tmp;

    if (*env_array == NULL) {
        init_own_env(env);
        return true;
    }
    tmp = separate_line(*env_array);
    if (tmp == NULL)
        return false;
    insert_in_env(tmp[0], tmp[1], env);
    free_array(tmp);
    return fill_the_list(env, env_array + 1);
}

env_t *init_env(char const **env_array)
{
    env_t *env = malloc(sizeof(env_t));

    if (env == NULL)
        return NULL;
    env->shell_variables = calloc(sizeof(env_list_t *), 1);
    env->env_list = calloc(sizeof(env_list_t *), 1);
    env->aliases = calloc(sizeof(env_list_t *), 1);
    if (!env->env_list || !env->shell_variables || !env->aliases)
        return NULL;
    env->last_return = 0;
    if (!fill_the_list(env->env_list, env_array))
        return NULL;
    env->old_pwd = search_env_value("OLD_PWD", env->env_list);
    env->old_pwd = (env->old_pwd == NULL) ?
        (strdup("")) : (strdup(env->old_pwd));
    return env;
}
