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

static bool add_command_history_file(int index, char *command,
    char *history_path)
{
    int file = open(history_path, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (file == -1) {
        perror("open");
        return false;
    }
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

static void free_empty_node(history_list_t **history)
{
    history_list_t *tmp = NULL;

    if ((*history) == NULL)
        return;
    tmp = (*history)->next;
    if ((*history)->command != NULL)
        free((*history)->command);
    free((*history));
    *history = tmp;
    if (tmp != NULL)
        (*history)->prev = NULL;
}

bool add_command_history(char *input, history_list_t **history,
    char *history_path)
{
    if (input == NULL || strcmp(input, "\0") == 0)
        return true;
    move_history_start(history);
    free_empty_node(history);
    if (!push_command_history(history, input))
        return false;
    if (history == NULL || !add_command_history_file((*history)->index,
    (*history)->command, history_path))
        return false;
    if (!push_command_history(history, ""))
        return false;
    return true;
}
