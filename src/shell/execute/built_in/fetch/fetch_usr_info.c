/*
** EPITECH PROJECT, 2024
** fetch_usr_info
** File description:
** fetch_usr_info
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

char *get_host(env_t *)
{
    char *buffer = NULL;
    char **data = NULL;
    char *host = NULL;
    size_t i = 0;
    FILE *file = fopen("/sys/devices/virtual/dmi/id/product_name", "r");

    if (file == NULL || getline(&buffer, &i, file) == -1)
        return NULL;
    data = format_arguments(buffer, "\n", "");
    if (data == NULL)
        return NULL;
    host = strdup(data[0]);
    if (host == NULL)
        return NULL;
    free(buffer);
    free_array(data);
    fclose(file);
    return host;
}

char *get_shell(env_t *)
{
    char *shell = strdup("BDShell");

    if (shell == NULL)
        return NULL;
    return shell;
}

static char *compute_uptime(long time)
{
    const long minute = 60;
    const long hour = minute * 60;
    const long day = hour * 24;
    char *uptime = NULL;
    char buffer[256] = {0};

    if (time == 0)
        return NULL;
    if (sprintf(buffer, "%ld days, %ld hours, %02ld mins", time / day,
    (time % day) / hour, (time % hour) / minute) == -1)
        return NULL;
    uptime = strdup(buffer);
    return uptime;
}

char *get_uptime(env_t *)
{
    char *uptime = NULL;
    char *buffer = NULL;
    char **data = NULL;
    size_t i = 0;
    FILE *file = fopen("/proc/uptime", "r");

    if (file == NULL || getline(&buffer, &i, file) == -1)
        return NULL;
    data = format_arguments(buffer, "\n ", "");
    if (data == NULL)
        return NULL;
    uptime = compute_uptime(atol(data[0]));
    free(buffer);
    free_array(data);
    fclose(file);
    return uptime;
}
