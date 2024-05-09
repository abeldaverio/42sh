/*
** EPITECH PROJECT, 2024
** fetch_display
** File description:
** fetch_display
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "colors.h"
#include "env.h"
#include "fetch_info.h"
#include "fetch_theme.h"
#include "functions.h"

static int buffer_size(char const *filepath)
{
    struct stat sb;

    if (stat(filepath, &sb) == -1) {
        perror("stat");
        return -1;
    }
    return sb.st_size;
}

char *create_buffer(char *filepath)
{
    int buf_size = 0;
    char *buffer = NULL;
    int file = open(filepath, O_RDONLY);

    if (file == -1)
        return NULL;
    buf_size = buffer_size(filepath);
    if (buf_size == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (buf_size + 1));
    if (buffer == NULL)
        return NULL;
    if (read(file, buffer, buf_size) == -1)
        return NULL;
    buffer[buf_size] = '\0';
    close(file);
    return buffer;
}

static char *get_dash(env_t *env)
{
    char *dash = NULL;
    char *username = search_env_value("USER", env->env_list);
    char *hostname = search_env_value("HOSTNAME", env->env_list);
    int len = 0;

    if (username != NULL && hostname != NULL)
        len = strlen(username) + strlen(hostname) + 1;
    dash = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; ++i)
        dash[i] = '-';
    dash[len] = '\0';
    return dash;
}

static void display_fetch_info(env_t *env, fetch_model_t model,
    size_t *i, size_t count)
{
    char *data = NULL;

    if (count > 1 && count <= 2 && *i < SIZE_FETCH_INFO) {
        dprintf(1, "\t\t%s%s%s@%s%s", FETCH_THEME[model].color,
        search_env_value("USER", env->env_list), DEFAULT,
        FETCH_THEME[CAMILLE].color,
        search_env_value("HOSTNAME", env->env_list));
    }
    if (count > 2 && count <= 3 && *i < SIZE_FETCH_INFO) {
        data = get_dash(env);
        dprintf(1, "\t\t%s", data);
    }
    if (count > 3 && *i < SIZE_FETCH_INFO) {
        data = FETCH_INFO[*i].data(env);
        dprintf(1, "\t\t%s%s%s: %s", FETCH_THEME[model].color,
        FETCH_INFO[*i].var, DEFAULT, (data != NULL ? data : "unknown"));
        *i = *i + 1;
    }
    if (data != NULL)
        free(data);
}

static void display_colors_shell(env_t *env)
{
    char **data = NULL;
    char **colors = NULL;

    colors = get_colors(env);
    if (colors == NULL)
        return;
    dprintf(1, "\t\t");
    for (int i = 0; colors[i] != NULL; ++i) {
        data = format_arguments(colors[i], ";m[", "");
        if (data == NULL || data[0] == NULL)
            break;
        if (my_arraylen(data) == 1)
            dprintf(1, "\033[%dm   ", atoi(data[0]) + 10);
        if (my_arraylen(data) == 2)
            dprintf(1, "\033[%dm   ", atoi(data[1]) + 10);
        free_array(data);
    }
    dprintf(1, "%s", DEFAULT);
    free_array(colors);
}

static void display_fetch(env_t *env, char *fetch, fetch_model_t model)
{
    size_t i = 0;

    for (size_t count = 0; fetch != NULL; count ++) {
        dprintf(1, "%s", fetch);
        if (count > 1 && i < SIZE_FETCH_INFO)
            display_fetch_info(env, model, &i, count);
        if (count == SIZE_FETCH_INFO + 5)
            display_colors_shell(env);
        dprintf(1, "\n");
        fetch = strtok(NULL, "\n");
    }
}

bool fetch_command(char **args, env_t *env, fetch_model_t model)
{
    char *buffer = NULL;
    char *fetch = NULL;

    if (my_arraylen(args) != 1)
        return false;
    buffer = create_buffer(FETCH_THEME[model].filepath);
    if (buffer == NULL)
        return false;
    fetch = strtok(buffer, "\n");
    if (fetch == NULL)
        return false;
    display_fetch(env, fetch, model);
    free(buffer);
    return true;
}
