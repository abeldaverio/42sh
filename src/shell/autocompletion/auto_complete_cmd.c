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
    glob_t globbuf = {0};
    char *concat_path = NULL;

    if (to_complete[0] == '\0')
        return NULL;
    concat_path = my_strcat(3, "/bin/", to_complete, "*");
    glob(concat_path, GLOB_DOOFFS, NULL, &globbuf);
    free(concat_path);
    concat_path = my_strcat(3, "/usr/bin/", to_complete, "*");
    glob(concat_path, GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
    free(concat_path);
    candidates = my_arraydup(globbuf.gl_pathv);
    globfree(&globbuf);
    return candidates;
}

int auto_compete_cmd(char *complete, int *completion_ptr)
{
    char **candidates = NULL;
    int lines_printed = 0;

    candidates = get_command_completion(complete);
    if (candidates != NULL && candidates[0] != NULL) {
        lines_printed = print_completion(candidates, completion_ptr);
        free_array(candidates);
    }
    return lines_printed;
}
