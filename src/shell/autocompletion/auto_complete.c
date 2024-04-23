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

static char *alloc_completion(char *input, int *counter_ptr)
{
    char *new_str = NULL;
    int counter = 0;

    for (int i = strlen(input) - 1; i >= 0; i--) {
        if (input[i] == ' ' || input[i] == '\0' || input[i] == '\t') {
            break;
        }
        counter++;
    }
    if (counter <= 0)
        return NULL;
    new_str = calloc(counter + 1, sizeof(char));
    *counter_ptr = counter;
    return new_str;
}

char *get_completion(char *input)
{
    int counter = 0;
    char *new_str = alloc_completion(input, &counter);
    int counter_dup = 0;

    if (new_str == NULL)
        return NULL;
    counter -= 1;
    for (int i = counter; i >= 0; i--) {
        new_str[i] = input[(strlen(input) - 1) - counter_dup];
        counter_dup++;
    }
    return new_str;
}

static size_t get_win_offset(size_t lenbigest)
{
    int offset = 10;
    struct winsize w = {0};

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    offset = w.ws_col / 27;
    if (lenbigest >= MAX_RANGE[END])
        offset = 1;
    return (offset);
}

static size_t get_bigest_len(char **completions)
{
    size_t max = 0;
    char **formated = NULL;
    size_t format_size = 0;
    size_t format_index = 0;

    for (int i = 0; completions[i] != NULL; i++) {
        formated = format_arguments(completions[i], "/", "");
        format_index = my_arraylen(formated) - 1;
        format_size = strlen(formated[format_index]);
        if (format_size > max)
            max = format_size;
        free_array(formated);
    }
    return max;
}

static void print_pretty(char *formated)
{
    size_t format_size = strlen(formated);

    if (format_size >= MAX_RANGE[BEG])
        dprintf(1, "%s\t", formated);
    if (format_size >= MID_RANGE[BEG] && format_size <= MID_RANGE[END])
        dprintf(1, "%s\t\t", formated);
    if (format_size >= SMALL_RANGE[BEG] && format_size <= SMALL_RANGE[END])
        dprintf(1, "%s\t\t\t", formated);
}

int print_completion(char **completions)
{
    char **formated = NULL;
    size_t format_index = 0;
    int last_element = my_arraylen(completions) - 1;
    size_t offset = get_win_offset(get_bigest_len(completions));
    int lines_printed = 0;
    size_t reset_counter = 0;

    for (int i = 0; completions[i] != NULL; i++) {
        formated = format_arguments(completions[i], "/", "");
        format_index = my_arraylen(formated) - 1;
        reset_counter += 1;
        if (reset_counter == offset) {
            reset_counter = 0;
            lines_printed += dprintf(1, "\n");
        }
        print_pretty(formated[format_index]);
        dprintf(1, i == last_element ? "\n" : "");
        free_array(formated);
    }
    return lines_printed;
}

int auto_complete(char *input)
{
    char *to_complete = NULL;
    bool we_free = true;
    int lines_printed = 0;

    to_complete = get_completion(input);
    if (to_complete == NULL) {
        to_complete = "";
        we_free = false;
    }
    lines_printed = auto_compete_cmd(to_complete);
    if (lines_printed)
        auto_compete_dir(to_complete);
    if (we_free)
        free(to_complete);
    return lines_printed;
}
