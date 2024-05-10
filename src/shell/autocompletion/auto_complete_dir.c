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
#include "macros.h"
#include "complete.h"

static char **get_dir_completion(char *to_complete)
{
    char **candidates = NULL;
    char *concat_path = NULL;
    glob_t globbuf;

    globbuf.gl_offs = 0;
    concat_path = my_strcat(2, to_complete, "*");
    if (concat_path == NULL)
        return NULL;
    glob(concat_path, GLOB_DOOFFS, NULL, &globbuf);
    candidates = my_arraydup(CONST_A(globbuf.gl_pathv));
    globfree(&globbuf);
    free(concat_path);
    return candidates;
}

int *auto_compete_dir(char *complete, int completion_ptr, int info[3])
{
    char **candidates = NULL;
    int *lines_info = NULL;

    candidates = get_dir_completion(complete);
    if (candidates == NULL) {
        return NULL;
    }
    if (candidates[0] == NULL) {
        free_array(candidates);
        return NULL;
    }
    lines_info = print_completion(candidates, completion_ptr, info);
    free_array(candidates);
    return lines_info;
}

char *auto_compete_dir_get(char *complete, int completion_ptr)
{
    char **candidates = NULL;
    char *completion = NULL;

    if (completion == NULL)
        completion = "";
    candidates = get_dir_completion(complete);
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
