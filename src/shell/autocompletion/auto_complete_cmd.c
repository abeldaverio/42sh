/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** auto complete
*/

#include "functions.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "complete.h"

static char **get_command_completion(char *to_complete)
{
    char **candidates = NULL;
    glob_t globbuf;
    char *concat_path = NULL;

    globbuf.gl_offs = 0;
    if (to_complete[0] == '\0')
        return NULL;
    concat_path = my_strcat(3, "/bin/", to_complete, "*");
    if (concat_path == NULL)
        return NULL;
    glob(concat_path, GLOB_DOOFFS, NULL, &globbuf);
    free(concat_path);
    concat_path = my_strcat(3, "/usr/bin/", to_complete, "*");
    if (concat_path == NULL)
        return NULL;
    glob(concat_path, GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
    free(concat_path);
    candidates = my_arraydup(globbuf.gl_pathv);
    globfree(&globbuf);
    return candidates;
}

int *auto_compete_cmd(char *complete, int completion_ptr, int info[3])
{
    char **candidates = NULL;
    int *lines_info = NULL;

    candidates = get_command_completion(complete);
    if (candidates == NULL)
        return NULL;
    if (candidates[0] == NULL) {
        free_array(candidates);
        return NULL;
    }
    lines_info = print_completion(candidates, completion_ptr, info);
    free_array(candidates);
    return lines_info;
}

char *auto_compete_cmd_get(char *complete, int completion_ptr)
{
    char **candidates = NULL;
    char *completion = NULL;

    candidates = get_command_completion(complete);
    if (candidates == NULL) {
        return NULL;
    }
    if (candidates[0] == NULL) {
        free_array(candidates);
        return NULL;
    }
    if (completion_ptr != -1)
        completion = isolate_completion(candidates, completion_ptr);
    free_array(candidates);
    return completion;
}
