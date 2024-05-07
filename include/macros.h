/*
** EPITECH PROJECT, 2024
** macros
** File description:
** macros
*/

#include <stddef.h>

#ifndef MACROS_H
    #define MACROS_H

    #define ERROR_STATUS 84
    #define SUCCESS_STATUS 0
    #define EXIT_CODE 42
    #define ABS(x) ((x < 0) ? (-1 * (x)) : ((x)))
    #define KEY_ESCAPE  0x001b
    #define KEY_ENTER   0x000a
    #define KEY_TAB     0x0009
    #define KEY_UP      0x0105
    #define KEY_DOWN    0x0106
    #define KEY_LEFT    0x0107
    #define KEY_RIGHT   0x0108
    #define KEY_DEL     0x7f
    #define KEY_SUPP 0x7e

void cursor_backward(size_t i);
void history(char *line);
void delete(size_t i);
size_t delete_command(size_t index, char **line);
void back_command(char *line);
void front_command(char *line);
void cursor_forward(size_t i);
void enter(char *line);

typedef enum pipe_fd_s {
    OUT,
    IN
} pipe_fd_t;

#endif /* !MACROS_H */
