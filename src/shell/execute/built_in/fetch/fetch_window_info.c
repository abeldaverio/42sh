/*
** EPITECH PROJECT, 2024
** fetch_window_info
** File description:
** fetch_window_info
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "env.h"
#include "fetch_info.h"
#include "fetch_theme.h"
#include "functions.h"

char *get_desktop_environment(env_t *env)
{
    char *desktop_environment = NULL;
    char *data = search_env_value("XDG_CURRENT_DESKTOP", env->env_list);

    if (data == NULL)
        return NULL;
    desktop_environment = strdup(data);
    if (desktop_environment == NULL)
        return NULL;
    return desktop_environment;
}

char *get_resolution(env_t *)
{
    char *resolution = NULL;
    char *buffer = NULL;
    char **data = NULL;
    size_t i = 0;
    FILE *cmd = popen("xdpyinfo | awk '/dimensions/ {print $2}'", "r");

    if (cmd == NULL || getline(&buffer, &i, cmd) == -1)
        return NULL;
    data = format_arguments(buffer, "\n ", "");
    if (data == NULL)
        return NULL;
    resolution = strdup(data[0]);
    free(buffer);
    free_array(data);
    pclose(cmd);
    return resolution;
}
