/*
** EPITECH PROJECT, 2024
** history
** File description:
** history
*/

#ifndef HISTORY_H
    #define HISTORY_H

    #include <stdbool.h>
    #define HISTORY_PATH "./.history"
    #define HISTORY_FILE_NAME ".history"

typedef struct history_list_s {
    int index;
    char *command;
    struct history_list_s *prev;
    struct history_list_s *next;
} history_list_t;

history_list_t *create_history(void);
bool push_command_history(history_list_t **history, char *input);
bool add_command_history(char *input, history_list_t **history,
    char *history_path);
void free_history(history_list_t *history);
char *create_buffer(char *filepath);

#endif /* !HISTORY_H */
