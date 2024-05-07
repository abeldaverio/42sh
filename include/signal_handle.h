/*
** EPITECH PROJECT, 2024
** signal handle
** File description:
** regroup all the andled signal and their functions
*/

#ifndef SIGNAL_H
    #define SIGNAL_H

    #include <signal.h>

typedef struct signal_handle_s {
    int signal;
    void (*function)(int);
}signal_handle_t;

void handle_sigtstp(int);
void handle_sigint(int);

static const signal_handle_t SIGNAL_LIST[] = {
    {SIGINT, handle_sigint},
    {SIGTSTP, handle_sigtstp},
};

static const size_t SIGNAL_SIZE =
sizeof(SIGNAL_LIST) / sizeof(signal_handle_t);

#endif
