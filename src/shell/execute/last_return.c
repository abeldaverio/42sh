/*
** EPITECH PROJECT, 2024
** last return
** File description:
** update ? shell variables
*/

#include <stddef.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "functions.h"

void update_status(int status, env_t *env)
{
    if (WIFEXITED(status)) {
        env->last_return = WEXITSTATUS(status);
    } else {
        dprintf(2, "%s\n", strsignal((status > 128) ? status - 128 : status));
        env->last_return = (status < 128) ? status + 128 : status;
    }
}

void wait_child(int child_pid, env_t *env)
{
    int status = 0;

    waitpid(child_pid, &status, WUNTRACED);
    if (WEXITSTATUS(status) > 128)
        update_status(status, env);
}
