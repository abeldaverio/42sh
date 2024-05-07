/*
** EPITECH PROJECT, 2024
** add_command_history
** File description:
** add_command_history
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

static bool add_command_history_file(int index, char *command)
{
    int file = open(HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (file == -1)
        return false;
    dprintf(file, "%d: %s\n", index, command);
    close(file);
    return true;
}

bool add_command_history(char *input, history_list_t **history)
{
    if (input == NULL || strcmp(input, "\n") == 0)
        return false;
    if (!push_command_history(history, input))
        return false;
    if (history == NULL ||
    !add_command_history_file((*history)->index, (*history)->command))
        return false;
    return true;
}

void get_prev_history(history_list_t **history)
{
    return;
}

void get_next_history(history_list_t **history)
{
    return;
}
