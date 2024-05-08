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

bool push_command_history(history_list_t **history, char *input)
{
    history_list_t *node = malloc(sizeof(history_list_t));
    char **data = NULL;

    if (node == NULL || input == NULL)
        return false;
    data = format_arguments(input, "\n", "");
    if (data == NULL)
        return false;
    node->index = (*history == NULL) ? 1 : (*history)->index + 1;
    node->command = (data[0] == NULL ? strdup("") : strdup(data[0]));
    if (node->command == NULL)
        return false;
    node->prev = NULL;
    node->next = *history;
    *history = node;
    if (node->next != NULL)
        node->next->prev = node;
    free_array(data);
    return true;
}

static void move_history_start(history_list_t **history)
{
    if (*history == NULL)
        return;
    while ((*history)->prev != NULL) {
        (*history) = (*history)->prev;
    }
}

bool add_command_history(char *input, history_list_t **history)
{
    if (input == NULL || strcmp(input, "\0") == 0)
        return true;
    move_history_start(history);
    if (!push_command_history(history, input))
        return false;
    if (history == NULL ||
    !add_command_history_file((*history)->index, (*history)->command))
        return false;
    return true;
}
