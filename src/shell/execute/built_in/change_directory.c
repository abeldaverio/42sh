/*
** EPITECH PROJECT, 2024
** change directory
** File description:
** command cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "macros.h"
#include "env.h"
#include "functions.h"
#include "built_in.h"

static void update_pwd(env_list_t **env_list, char *buff)
{
    char *new_old_pwd = strdup(buff);
    char *new_pwd = strdup(getcwd(buff, 255));

    if (new_pwd == NULL || new_old_pwd == NULL)
        exit(ERROR_STATUS);
    insert_in_env("PWD", new_pwd, env_list);
    insert_in_env("OLDPWD", new_old_pwd, env_list);
    free(new_old_pwd);
    free(new_pwd);
}

static void go_home(env_t *env, char *buff)
{
    char *tmp = search_env_value("HOME", env->env_list);

    buff = getcwd(buff, 255);
    if (buff == NULL)
        exit(ERROR_STATUS);
    if (tmp != NULL) {
        chdir(search_env_value("HOME", env->env_list));
        update_pwd(env->env_list, buff);
        env->last_return = 0;
    } else {
        dprintf(2, "cd: No home directory.\n");
        env->last_return = 1;
    }
}

static void go_back(env_t *env, char *buff)
{
    char *tmp = search_env_value("OLDPWD", env->env_list);

    buff = getcwd(buff, 255);
    if (buff == NULL)
        exit(ERROR_STATUS);
    if (tmp != NULL) {
        chdir(tmp);
        update_pwd(env->env_list, buff);
        env->last_return = 0;
    } else {
        dprintf(2, ": No such file or directory.\n");
        env->last_return = 1;
    }
}

static void print_errors(char *path)
{
    if (errno == ENOENT) {
        dprintf(2, "%s: No such file or directory.\n", path);
    }
    if (errno == ENOTDIR) {
        dprintf(2, "%s: Not a directory.\n", path);
    }
    if (errno == EACCES) {
        dprintf(2, "%s: Permission denied.\n", path);
    }
}

static void normal_change(char *path, env_t *env, char *buff)
{
    buff = getcwd(buff, 255);
    if (buff == NULL)
        exit(ERROR_STATUS);
    if (buff == NULL)
        exit(ERROR_STATUS);
    if (chdir(path) == -1) {
        dprintf(2, "cd: ");
        print_errors(path);
        env->last_return = 1;
        return;
    }
    update_pwd(env->env_list, buff);
    env->last_return = 0;
}

bool change_directory(char **argv, env_t *env)
{
    char buff[255];

    if (my_arraylen(CONST_A(argv)) > 2) {
        dprintf(2, "cd: Too many arguments.\n");
        env->last_return = 1;
        return true;
    }
    if (my_arraylen(CONST_A(argv)) == 1 || strcmp(argv[1], "~") == 0) {
        go_home(env, buff);
        return true;
    }
    if (strcmp(argv[1], "-") == 0) {
        go_back(env, buff);
        return true;
    }
    normal_change(argv[1], env, buff);
    return true;
}
