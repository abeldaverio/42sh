/*
** EPITECH PROJECT, 2024
** struct with the main infos of the env
** File description:
** ah
*/

#ifndef SHELL_COMMAND_H
    #define SHELL_COMMAND_H

    #include <stdbool.h>
    #include "env.h"

typedef struct command_s {
    char *command;
    bool (*function)(char **argv, env_t *env);
}command_t;

//functions
bool display_env(char **argv, env_t *env);
bool set_env(char **argv, env_t *env);
bool unset_env(char **argv, env_t *env);
bool change_directory(char **argv, env_t *env);
bool set_exit_value(char **argv, env_t *env);
bool set_alias(char **argv, env_t *env);
bool unset_alias(char **argv, env_t *env);
bool camille_fetch(char **argv, env_t *env);

static const command_t COMMANDS[] = {
    {"cd", change_directory},
    {"env", display_env},
    {"setenv", set_env},
    {"unsetenv", unset_env},
    {"exit", set_exit_value},
    {"alias", set_alias},
    {"unalias", unset_alias},
    {"camillefetch", camille_fetch}
};

static const int NB_OF_COMMANDS = sizeof(COMMANDS) / sizeof(command_t);

#endif
