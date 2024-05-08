/*
** EPITECH PROJECT, 2024
** handle sigint
** File description:
** handle ctrl c
*/

#include <stdio.h>
#include "macros.h"

void handle_sigint(int)
{
    fprintf(stdin, "%c", CTRL_C);
    fflush(stdin);
    return;
}
