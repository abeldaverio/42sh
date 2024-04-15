/*
** EPITECH PROJECT, 2024
** init pwd
** File description:
** init
*/

#include <unistd.h>
#include <stdlib.h>
#include "env.h"
#include "functions.h"

bool init_pwd(env_list_t **env)
{
    char *pwd = getcwd(NULL, 0);

    if (pwd == NULL)
        return false;
    insert_in_env("PWD", pwd, env);
    free(pwd);
    return true;
}
