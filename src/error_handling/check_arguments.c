/*
** EPITECH PROJECT, 2024
** check_arguments
** File description:
** check_arguments
*/

#include <stdbool.h>
#include <stdio.h>

bool check_main_args(int const argc)
{
    if (argc != 1) {
        dprintf(2, "mysh: arguments are not supported: error\n");
        return false;
    }
    return true;
}
