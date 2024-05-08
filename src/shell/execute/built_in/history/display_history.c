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
#include "env.h"
#include "history.h"
#include "functions.h"

static void display_history_line(history_list_t *history, int count, int n)
{
    if (history == NULL || n == count)
        return;
    display_history_line(history->next, count, n + 1);
    dprintf(1, "%d: %s\n", history->index, history->command);
}

static bool display_n_history_line(char **args,
    history_list_t *history)
{
    char *end = NULL;
    int n = strtol(args[1], &end, 10);

    if (strcmp(end, "\0") != 0 || n < 0)
        return false;
    display_history_line(history, n, 0);
    return true;
}

bool display_history(char **args, env_t *env)
{
    history_list_t *tmp_history = env->history;

    if (tmp_history == NULL)
        return true;
    if (my_arraylen(args) > 2) {
        dprintf(2, "history: Too many arguments.\n");
        env->last_return = 1;
        return true;
    }
    if (my_arraylen(args) == 1)
        display_history_line(tmp_history, tmp_history->index, 0);
    else if (!display_n_history_line(args, tmp_history)) {
        dprintf(2, "history: Badly formed number.\n");
        env->last_return = 1;
        return true;
    }
    env->last_return = 0;
    return true;
}
