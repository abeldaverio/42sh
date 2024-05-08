/*
** EPITECH PROJECT, 2024
** history
** File description:
** history
*/

#ifndef HISTORY_H
    #define HISTORY_H

    #include <stdbool.h>
    #define HISTORY_PATH "./history"

typedef struct history_list_s {
    int index;
    char *command;
    struct history_list_s *prev;
    struct history_list_s *next;
} history_list_t;

history_list_t *create_history(void);
//void move_history_start(history_list_t *history);
bool push_command_history(history_list_t **history, char *input);
bool add_command_history(char *input, history_list_t **history);
void free_history(history_list_t *history);
char *create_buffer(char *filepath);

#endif /* !HISTORY_H */
