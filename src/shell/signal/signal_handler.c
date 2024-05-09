/*
** EPITECH PROJECT, 2024
** signal handler
** File description:
** handle the differents signals
*/

#include <stdbool.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include "signal_handle.h"

bool signal_handler(void)
{
    for (size_t i = 0; i < SIGNAL_SIZE; ++i) {
        if (signal(SIGNAL_LIST[i].signal,
            SIGNAL_LIST[i].function) == SIG_ERR) {
            perror("signal");
            return false;
        }
    }
    return true;
}
