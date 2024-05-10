/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** auto complete
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "complete.h"
#include "functions.h"

char *get_completion_result(char *input, int completion_ptr)
{
    char *to_complete = NULL;
    bool we_free = true;
    char *completion = NULL;

    to_complete = get_completion(input, false);
    if (to_complete == NULL) {
        to_complete = "";
        we_free = false;
    }
    completion = auto_compete_cmd_get(to_complete, completion_ptr);
    if (completion == NULL)
        completion = auto_compete_dir_get(to_complete, completion_ptr);
    if (we_free)
        free(to_complete);
    return completion;
}

int *auto_complete(char *input, int completion_ptr, int info[3])
{
    char *to_complete = NULL;
    bool we_free = true;
    int *lines_info = NULL;

    to_complete = get_completion(input, false);
    if (to_complete == NULL) {
        to_complete = "";
        we_free = false;
    }
    lines_info = auto_compete_cmd(to_complete, completion_ptr, info);
    if (lines_info == NULL)
        lines_info = auto_compete_dir(to_complete, completion_ptr, info);
    if (we_free)
        free(to_complete);
    return lines_info;
}
