/*
** EPITECH PROJECT, 2024
** struct with the main infos of the env
** File description:
** ah
*/

#ifndef SHELL_COMMAND_H
    #define SHELL_COMMAND_H

    #include "env.h"

typedef struct command_s {
    char *command;
    void (*function)(char **argv, env_t *env);
}command_t;

//functions
void display_env(char **argv, env_t *env);
void set_env(char **argv, env_t *env);
void unset_env(char **argv, env_t *env);
void change_directory(char **argv, env_t *env);

static const command_t COMMANDS[] = {
    {"cd", change_directory},
    {"env", display_env},
    {"setenv", set_env},
    {"unsetenv", unset_env},
};

static const int NB_OF_COMMANDS = sizeof(COMMANDS) / sizeof(command_t);

#endif
