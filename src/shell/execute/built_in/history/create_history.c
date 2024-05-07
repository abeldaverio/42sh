/*
** EPITECH PROJECT, 2024
** create_history_array
** File description:
** create_history_array
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

void free_history(history_list_t *history)
{
    if (history == NULL)
        return;
    free_history((history)->next);
    if (history != NULL) {
        if (history->command != NULL)
            free(history->command);
        free(history);
    }
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
    node->command = strdup(data[0]);
    if (node->command == NULL)
        return false;
    node->prev = NULL;
    node->next = *history;
    *history = node;
    free_array(data);
    return true;
}

history_list_t *create_history(void)
{
    history_list_t *history = NULL;
    size_t i = 0;
    char *line = NULL;
    FILE *file = fopen(HISTORY_PATH, "a+");

    while (getline(&line, &i, file) != -1)
        if (!push_command_history(&history, line))
            return NULL;
    if (line != NULL)
        free(line);
    fclose(file);
    return history;
}
