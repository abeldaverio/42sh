/*
** EPITECH PROJECT, 2024
** handle a command in the shell
** File description:
** .
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "macros.h"
#include "built_in.h"
#include "functions.h"

static int try_shell_command(char **args, env_t *env)
{
    for (int i = 0; i < NB_OF_COMMANDS; i++) {
        if (strcmp(args[0], COMMANDS[i].command) == 0) {
            return (COMMANDS[i].function)(args, env);
        }
    }
    return 2;
}

static char *concatenate_path(char *str1, char *str2)
{
    char *tmp;

    if (str1[strlen(str1) - 1] == '/')
        return strcat(str1, str2);
    else {
        tmp = my_strcat(3, str1, "/", str2);
        if (tmp == NULL)
            exit(84);
        return tmp;
    }
}

static bool try_path(char **args, char *path, env_t *env)
{
    char *executable = concatenate_path(path, args[0]);
    struct stat sb;

    if (lstat(executable, &sb) != -1) {
        execute_file(executable, args, env);
        free(executable);
        return true;
    }
    free(executable);
    return false;
}

char **get_path(env_list_t **env)
{
    if (*env == NULL)
        return NULL;
    if (strcmp((*env)->variable, "PATH") == 0)
        return format_arguments((*env)->value, ":", "");
    return get_path(&(*env)->next);
}

static bool try_path_command(char **args, env_t *env)
{
    char **paths = get_path(env->env_list);

    if (paths == NULL)
        return false;
    for (int i = 0; paths[i] != NULL; i++)
        if (try_path(args, paths[i], env)) {
            free_array(paths);
            return true;
        }
    free_array(paths);
    if (try_path(args, "/usr/bin", env))
        return true;
    return false;
}

bool is_it_command(char **args)
{
    if (strcmp(args[0], "..") == 0 || strcmp(args[0], ".") == 0)
        return false;
    for (int i = 0; args[0][i] != '\0' && args[0][i] != '\n'; i++) {
        if (args[0][i] == '/' || args[0][i] == '=')
            return false;
    }
    return true;
}

bool execute_comand(char **args, env_t *env)
{
    int built_in_return = 0;

    built_in_return = try_shell_command(args, env);
    if (built_in_return == 1)
        return true;
    if (built_in_return == 0)
        return false;
    if (try_path_command(args, env))
        return true;
    dprintf(2, "%s: Command not found.\n", args[0]);
    env->last_return = 1;
    return true;
}
