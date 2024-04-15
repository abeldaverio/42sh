/*
** EPITECH PROJECT, 2024
** possibility
** File description:
** all the possibility when typing with minishell
*/

#ifndef POSSIBILITY_H
    #define POSSIBILITY_H

    #include <stdbool.h>
    #include "env.h"

// check functions
bool is_it_append_variable(char **args);
bool is_it_command(char **args);
bool always_true(char **args);
bool is_it_variable(char **args);


// functions
bool append_to_variable(char **args, env_t *env);
bool execute_comand(char **args, env_t *env);
bool check_first_arg(char **args, env_t *env);
bool set_variable(char **args, env_t *env);

typedef struct poss_s {
    bool (*check)(char **args);
    bool (*function)(char **argv, env_t *env);
}poss_t;

static const poss_t POSSIBILITY[] = {
    {is_it_append_variable, append_to_variable},
    {is_it_variable, set_variable},
    {is_it_command, execute_comand},
    {always_true, check_first_arg},
};

static const int NB_OF_POSSIBILITY = sizeof(POSSIBILITY) / sizeof(poss_t);

#endif
