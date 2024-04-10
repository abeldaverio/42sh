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

void init_host(env_list_t **env)
{
    struct utsname tmp = {0};

    if (uname(&tmp) == -1) {
        perror("uname");
    }
    insert_in_env("HOSTNAME", tmp.nodename, env);
}
