/*
** EPITECH PROJECT, 2024
** get char
** File description:
** read
*/

#include <unistd.h>

char my_getchar(void)
{
    char buff[1] = {0};

    read(STDIN_FILENO, buff, 1);
    return buff[0];
}
