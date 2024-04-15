/*
** EPITECH PROJECT, 2024
** init host
** File description:
** init the host varable if env -i
*/

#include <stdbool.h>
#include <sys/utsname.h>
#include <stdio.h>
#include "env.h"
#include "functions.h"

bool init_utsname(env_list_t **env)
{
    struct utsname tmp = {0};

    if (uname(&tmp) == -1) {
        perror("uname");
        return false;
    }
    insert_in_env("HOSTNAME", tmp.nodename, env);
    insert_in_env("OSTYPE", tmp.sysname, env);
    insert_in_env("MATCHTYPE", tmp.machine, env);
    return true;
}
