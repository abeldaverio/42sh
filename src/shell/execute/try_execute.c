/*
** EPITECH PROJECT, 2024
** try execute
** File description:
** fon
*/

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void try_execute(char *path, char **args, char **env)
{
    if (execve(path, args, env) == -1) {
        if (errno == EACCES || errno == EISDIR) {
            dprintf(2, "%s: Permission denied.\n", path);
        } else {
            dprintf(2, "%s: : Exec format error. Wrong Architecture.\n", path);
        }
        exit(1);
    }
}
