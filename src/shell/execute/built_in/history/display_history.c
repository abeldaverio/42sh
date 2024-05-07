/*
** EPITECH PROJECT, 2024
** display_history
** File description:
** display_history
*/

#include <stddef.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "history.h"
#include "functions.h"

bool display_n_history_line(char **args, char *buffer)
{
    char *end = NULL;
    char **data = NULL;
    int nb_line = 0;
    int n = strtol(args[1], &end, 10);

    if (strcmp(end, "\0") != 0)
        return false;
    data = format_arguments(buffer, "\n", "");
    if (data == NULL)
        return false;
    nb_line = my_arraylen(data);
    for (int i = 0; i < n && n < nb_line; ++i)
        dprintf(1, "%s\n", data[nb_line - n + i]);
    if (n > nb_line)
        dprintf(1, "%s", buffer);
    if (n == 0)
        dprintf(1, "%s\n", data[nb_line - 1]);
    free_array(data);
    return true;
}

bool display_history(char **args, env_t *env)
{
    char *buffer = create_buffer(HISTORY_PATH);

    if (buffer == NULL || my_arraylen(args) > 2) {
        env->last_return = 1;
        dprintf(2, "history: Too many arguments.\n");
        return true;
    }
    if (my_arraylen(args) == 1)
        dprintf(1, "%s", buffer);
    else {
        if (!display_n_history_line(args, buffer)) {
            dprintf(2, "history: Badly formed number.\n");
            env->last_return = 1;
            free(buffer);
            return true;
        }
    }
    free(buffer);
    env->last_return = 0;
    return true;
}
