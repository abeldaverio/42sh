/*
** EPITECH PROJECT, 2024
** check line
** File description:
** function that execute after command line is entered
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "possibility.h"
#include "macros.h"
#include "functions.h"
#include "env.h"

static void replace_arg(char **origin, env_t *env)
{
    char *tmp = search_env_value((*origin) + 1, env->env_list);

    if (tmp == NULL)
        tmp = search_env_value((*origin) + 1, env->shell_variables);
    free(*origin);
    if (tmp == NULL)
        *origin = strdup("");
    else
        *origin = strdup(tmp);
}

static void replace_variables(char **args, env_t *env)
{
    if (*args == NULL)
        return;
    if (*args[0] == '$') {
        if (strcmp(*args, "$?") == 0) {
            free(*args);
            *args = int_to_str(env->last_return);
        } else {
            replace_arg(args, env);
        }
        if (*args == NULL)
            exit(ERROR_STATUS);
    }
    replace_variables(args + 1, env);
}

bool execute(char **args, env_t *env)
{
    bool return_value = true;

    replace_aliases(&args, env->aliases);
    replace_variables(args, env);
    for (int i = 0; i < NB_OF_POSSIBILITY; i++) {
        if (POSSIBILITY[i].check(args)) {
            return_value = POSSIBILITY[i].function(args, env);
            free_array(args);
            return return_value;
        }
    }
    exit(84);
}
