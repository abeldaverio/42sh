/*
** EPITECH PROJECT, 2024
** stumper
** File description:
** checks the file in the config dir
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#include "functions.h"

static char **stupid_dir_loop(DIR *conf_dir)
{
    struct dirent *info = readdir(conf_dir);
    int counter = 0;

    while (info != NULL) {
        if (info->d_name[0] != '.')
            counter++;
        info = readdir(conf_dir);
    }
    return calloc(counter + 1, sizeof(char *));
}

static char **alloc_file_arr(char *dir)
{
    DIR *conf_dir = NULL;
    char **to_alloc = NULL;

    if (dir == NULL)
        return NULL;
    conf_dir = opendir(dir);
    if (conf_dir == NULL) {
        if (dprintf(STDERR_FILENO,
            "Error :%s directory not found\n", dir))
            return NULL;
        return NULL;
    }
    to_alloc = stupid_dir_loop(conf_dir);
    closedir(conf_dir);
    return to_alloc;
}

static int8_t add_file_line(char **file_names,
    struct dirent *file_info, ssize_t file_counter)
{
    if (file_info->d_name[0] != '.') {
        if (file_names == NULL)
            return -1;
        file_names[file_counter] = strdup(file_info->d_name);
        file_names[file_counter + 1] = NULL;
        return 1;
    }
    return 0;
}

static bool read_config_dir(DIR *conf_dir, char **file_names)
{
    ssize_t file_counter = 0;
    struct dirent *file_info = readdir(conf_dir);
    int8_t temp_offset = 0;

    while (file_info != NULL) {
        temp_offset = add_file_line(file_names, file_info, file_counter);
        if (temp_offset == -1)
            return false;
        file_counter += temp_offset;
        file_info = readdir(conf_dir);
    }
    return true;
}

char **open_config_dir(char *dir)
{
    DIR *conf_dir = NULL;
    char **file_names = alloc_file_arr(dir);

    if (file_names == NULL)
        return NULL;
    conf_dir = opendir(dir);
    if (!read_config_dir(conf_dir, file_names))
        return NULL;
    if (closedir(conf_dir)) {
        free_array(file_names);
        return NULL;
    }
    return file_names;
}
