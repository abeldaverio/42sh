/*
** EPITECH PROJECT, 2024
** macros
** File description:
** macros
*/

#ifndef MACROS_H
    #define MACROS_H

    #define ERROR_STATUS 84
    #define SUCCESS_STATUS 0
    #define EXIT_CODE 42
    #define ABS(x) ((x < 0) ? (-1 * (x)) : ((x)))

typedef enum pipe_fd_s {
    OUT,
    IN
} pipe_fd_t;

#endif /* !MACROS_H */
