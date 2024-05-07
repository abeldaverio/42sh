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

static char **get_dir_completion(char *to_complete)
{
    char **candidates = NULL;
    char *concat_path = NULL;
    glob_t globbuf = {0};

    concat_path = my_strcat(2, to_complete, "*");
    glob(concat_path, GLOB_DOOFFS, NULL, &globbuf);
    candidates = my_arraydup(globbuf.gl_pathv);
    globfree(&globbuf);
    free(concat_path);
    return candidates;
}

int auto_compete_dir(char *complete, int *completion_ptr)
{
    char **candidates = NULL;
    int lines_printed = 0;

    candidates = get_dir_completion(complete);
    if (candidates != NULL && candidates[0] != NULL) {
        lines_printed = print_completion(candidates, completion_ptr);
        free_array(candidates);
    }
    return lines_printed;
}
