/*
** EPITECH PROJECT, 2024
** init vendor
** File description:
** put the vendor in env
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"
#include "paths.h"
#include "functions.h"

bool init_vendor(env_list_t **env)
{
    FILE *fd = fopen(VENDOR_FILE, "r");
    char *input = NULL;
    size_t tmp = 0;

    if (fd == NULL) {
        perror(VENDOR_FILE);
        return false;
    }
    if (getline(&input, &tmp, fd) == -1)
        insert_in_env("VENDOR", "unknown", env);
    else {
        input[strlen(input) - 1] = '\0';
        insert_in_env("VENDOR", input, env);
        free(input);
    }
    fclose(fd);
    return true;
}
