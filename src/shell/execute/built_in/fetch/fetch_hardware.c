/*
** EPITECH PROJECT, 2024
** fetch_hardware
** File description:
** fetch_hardware
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "env.h"
#include "fetch_info.h"
#include "fetch_theme.h"
#include "functions.h"

static int search_memory(FILE *file)
{
    size_t i = 0;
    char **data = NULL;
    char *buffer = NULL;
    int result = 0;

    if (getline(&buffer, &i, file) == -1)
        return -1;
    data = format_arguments(buffer, " \n", "");
    if (data == 0)
        return -1;
    if (my_arraylen(data) < 2)
        return -1;
    result = atoi(data[1]);
    if (result == 0)
        return -1;
    free(buffer);
    free_array(data);
    return result;
}

static char *compute_memory(FILE *file)
{
    char *memory = NULL;
    int total_memory = -1;
    int free_memory = -1;
    char tmp[256] = {0};

    total_memory = search_memory(file) / 1024;
    free_memory = search_memory(file) / 1024;
    free_memory = search_memory(file) / 1024;
    if (free_memory < 0 || total_memory < 0)
        return NULL;
    if (sprintf(tmp, "%dMib / %dMib", free_memory, total_memory) == -1)
        return NULL;
    memory = strdup(tmp);
    return memory;
}

char *get_memory(env_t *)
{
    char *memory = NULL;
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL)
        return NULL;
    memory = compute_memory(file);
    fclose(file);
    return memory;
}

static char *search_gpu(char *buffer)
{
    char **data = NULL;
    char *gpu = NULL;

    data = format_arguments(buffer, " \n", "\"");
    if (data == NULL)
        return NULL;
    if (my_arraylen(data) >= 4)
        gpu = my_strcat(3, data[2], " ", data[3]);
    free_array(data);
    return gpu;
}

char *get_gpu(env_t *)
{
    char *gpu = NULL;
    char *buffer = NULL;
    size_t i = 0;
    FILE *cmd = popen("lspci -mm | grep -i 'vga\\|3d\\|2d'", "r");

    if (cmd == NULL)
        return NULL;
    if (getline(&buffer, &i, cmd) == -1) {
        pclose(cmd);
        return NULL;
    }
    gpu = search_gpu(buffer);
    free(buffer);
    pclose(cmd);
    return gpu;
}

static char *search_cpu(char *const *data)
{
    char *cpu = NULL;

    for (int i = 0; data[i] != NULL; i++) {
        if (strcmp(data[i], "model name") == 0 && data[i + 1] != NULL) {
            cpu = strdup(data[i + 1] + 1);
            return cpu;
        }
    }
    return cpu;
}

char *get_cpu(env_t *)
{
    char *buffer = NULL;
    char *cpu = NULL;
    char **data = NULL;
    size_t i = 0;
    FILE *file = fopen("/proc/cpuinfo", "r");

    if (file == NULL)
        return NULL;
    while (getline(&buffer, &i, file) != -1 && cpu == NULL) {
        data = format_arguments(buffer, ":\t\n", "");
        if (data == NULL)
            return NULL;
        cpu = search_cpu(data);
        free_array(data);
    }
    free(buffer);
    fclose(file);
    return cpu;
}

char *get_kernel(env_t *)
{
    struct utsname name;
    char *kernel = NULL;

    uname(&name);
    kernel = strdup(name.release);
    if (kernel == NULL)
        return NULL;
    return kernel;
}

static char *search_os(char *const *data)
{
    char *os = NULL;
    bool next = false;

    for (int i = 0; data[i] != NULL; i++) {
        if (next) {
            os = strdup(data[i]);
            return os;
        }
        if (strcmp(data[i], "PRETTY_NAME") == 0)
            next = true;
    }
    return os;
}

char *get_os(env_t *)
{
    char *buffer = NULL;
    char *os = NULL;
    char **data = NULL;

    buffer = create_buffer("/etc/os-release");
    data = format_arguments(buffer, "=\"\n", "");
    if (data == NULL)
        return NULL;
    os = search_os(data);
    free_array(data);
    free(buffer);
    return os;
}
