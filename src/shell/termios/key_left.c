/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_left
*/

void cursor_backward(char *line)
{
    dprintf(1, "\033[%dC", 1);
}