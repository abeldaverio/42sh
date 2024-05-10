/*
** EPITECH PROJECT, 2024
** fetch_memory
** File description:
** fetch_memory
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

static int search_mem_data(char **mem_data, char *mem_var)
{
    char **data = NULL;
    int mem_nb = 0;

    for (int i = 0; mem_data[i] != NULL; ++i) {
        data = format_arguments(mem_data[i], " :\t\n", "");
        if (data == NULL || data[0] == NULL)
            return 0;
        if (strcmp(data[0], mem_var) == 0) {
            mem_nb = atoi(data[1]);
            free_array(data);
            return mem_nb;
        }
        free_array(data);
    }
    return 0;
}

static char *compute_memory(char **mem_data)
{
    char *memory = NULL;
    char tmp[256] = {0};
    int MemUsed = ((search_mem_data(mem_data, "MemTotal") +
    search_mem_data(mem_data, "Shmem") - search_mem_data(mem_data, "MemFree") -
    search_mem_data(mem_data, "Buffers") -
    search_mem_data(mem_data, "Cached") -
    search_mem_data(mem_data, "SReclaimable")) / 1024);

    if (sprintf(tmp, "%dMib / %dMib", MemUsed,
    search_mem_data(mem_data, "MemTotal") / 1024) == -1)
        return NULL;
    memory = strdup(tmp);
    return memory;
}

static char *get_memory_line(FILE *file)
{
    char *line = NULL;
    size_t i = 0;
    char **data = NULL;

    if (getline(&line, &i, file) != -1) {
        data = format_arguments(line, " :\t\n", "");
        if (data == NULL || data[0] == NULL)
            return NULL;
        if (strcmp(data[0], "MemTotal") == 0 || strcmp(data[0], "Shmem") == 0
        || strcmp(data[0], "MemFree") == 0 || strcmp(data[0], "Buffers") == 0
        || strcmp(data[0], "Cached") == 0 ||
        strcmp(data[0], "SReclaimable") == 0) {
            free_array(data);
            return line;
        }
        free_array(data);
    }
    if (line != NULL)
        free(line);
    return NULL;
}

static char **create_mem_data(FILE *file)
{
    char **mem_data = NULL;
    int count = 0;
    char *line = NULL;

    mem_data = malloc(sizeof(char *) * (6 + 1));
    if (mem_data == NULL)
        return NULL;
    for (int i = 0; count < 6 && i < 30; ++i) {
        line = get_memory_line(file);
        if (line != NULL) {
            mem_data[count] = line;
            count++;
        }
    }
    if (count < 6)
        return NULL;
    mem_data[count] = NULL;
    return mem_data;
}

char *get_memory(env_t *)
{
    char *memory = NULL;
    char **mem_data = NULL;
    FILE *file = fopen(MEMORY_PATH, "r");

    if (file == NULL)
        return NULL;
    mem_data = create_mem_data(file);
    if (mem_data == NULL)
        return NULL;
    memory = compute_memory(mem_data);
    free_array(mem_data);
    fclose(file);
    return memory;
}
