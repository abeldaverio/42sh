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
bool is_it_command(char **args);
bool always_true(char **args);
bool is_it_variable(char **args);

// functions
void execute_comand(char **args, env_t *env);
void check_first_arg(char **args, env_t *env);
void set_variable(char **args, env_t *env_list);

typedef struct poss_s {
    bool (*check)(char **args);
    void (*function)(char **argv, env_t *env);
}poss_t;

static const poss_t POSSIBILITY[] = {
    {is_it_variable, set_variable},
    {is_it_command, execute_comand},
    {always_true, check_first_arg},
};

static const int NB_OF_POSSIBILITY = sizeof(POSSIBILITY) / sizeof(poss_t);

#endif
