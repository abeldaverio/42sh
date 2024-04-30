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

void cursor_backward(char *line);
void history(char *line);
void delete(char *line);
void delete_command(char *line);
void back_command(char *line);
void front_command(char *line);
void cursor_forward(char *line);
void enter(char *line);

typedef struct flags {
    int flags;
    void (*d_f)(char *);
} fl;

static fl const tab[8] = {
    {KEY_UP, &front_command},
    {KEY_DOWN, &back_command},
    {KEY_LEFT, &cursor_backward},
    {KEY_RIGHT, &cursor_forward},
    {KEY_DEL, &delete_command},
    {KEY_TAB, &history},
    {KEY_ENTER, &enter},
    {0, NULL}
};

typedef enum pipe_fd_s {
    OUT,
    IN
} pipe_fd_t;

#endif /* !MACROS_H */
