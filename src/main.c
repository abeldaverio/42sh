/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for 42 sh
*/

#include "macros.h"
#include "functions.h"

int main(int const argc, char **, char const **env)
{
    if (!check_main_args(argc))
        return ERROR_STATUS;
    return start_shell(env);
}
