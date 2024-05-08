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

static bool push_line_history(history_list_t **history, char *input)
{
    char **data = NULL;
    int i = 0;

    if (input == NULL)
        return false;
    data = format_arguments(input, "\n", "");
    if (data == NULL)
        return false;
    while (data[0][i] != '\0' && data[0][i] != ':')
        ++i;
    if ((data[0] + i)[0] == '\0' || strlen(data[0] + i) <= 2) {
        free_array(data);
        return false;
    }
    if (!push_command_history(history, data[0] + i + 2)) {
        free_array(data);
        return false;
    }
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
        if (!push_line_history(&history, line))
            return NULL;
    if (line != NULL)
        free(line);
    fclose(file);
    return history;
}
