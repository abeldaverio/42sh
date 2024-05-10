/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_enter
*/

#include "complete.h"

void enter(char *line)
{
    reset_autocompletion(prompt, env);
    (void)line;
    return;
}
