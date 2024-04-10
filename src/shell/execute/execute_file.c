/*
** EPITECH PROJECT, 2024
** execute file
** File description:
** function to execute files
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "functions.h"

bool execute_file(char *executable, char **args, env_t *env)
{
    int wstatus;
    pid_t child_pid = fork();
    char **env_array = get_env_array(env->env_list);

    if (child_pid == -1)
        exit(84);
    if (child_pid == 0) {
        try_execute(executable, args, env_array);
    } else {
        if (waitpid(child_pid, &wstatus, WUNTRACED) == -1)
            exit(84);
        update_status(wstatus, env);
    }
    free_array(env_array);
    return true;
}
