/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** completion display
*/


#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

#include "functions.h"
#include "complete.h"


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

static int print_pretty(char *formated, bool hightlight)
{
    size_t format_size = strlen(formated);
    int chars_printed = 0;

    if (hightlight)
        chars_printed += dprintf(1, "\033[1;33m");
    if (format_size >= MAX_RANGE[BEG])
        chars_printed += dprintf(1, "%s\t", formated);
    if (format_size >= MID_RANGE[BEG] && format_size <= MID_RANGE[END])
        chars_printed += dprintf(1, "%s\t\t", formated);
    if (format_size >= SMALL_RANGE[BEG] && format_size <= SMALL_RANGE[END])
        chars_printed += dprintf(1, "%s\t\t\t", formated);
    if (hightlight)
        chars_printed += dprintf(1, "\033[0m");
    return chars_printed;
}

static int update_info(char **formated, bool is_last_element, bool highlight, int info[3])
{
    int temp_line_char = 0;
    size_t format_index = 0;

    format_index = my_arraylen(formated) - 1;
    temp_line_char += print_pretty(formated[format_index], highlight);
    temp_line_char += dprintf(1, is_last_element ? "\n" : "");
    info[CHARS_INFO] += temp_line_char;
    free_array(formated);
    return temp_line_char;
}

static int *is_reset(size_t *reset_counter, size_t offset, int info[3], int *lines_info)
{
    if (*reset_counter == offset) {
        *reset_counter = 0;
        info[CHARS_INFO] += dprintf(1, "\n");
        info[LINES_INFO] += 1;
        return realloc(lines_info, sizeof(int) * (info[LINES_INFO] + 1));
    }
    return lines_info;
}

int *print_completion(char **completions, int completion_ptr, int info[3])
{
    char **formated = NULL;
    size_t offset = get_win_offset(get_bigest_len(completions));
    size_t reset_counter = 0;
    int *lines_info = calloc(1, sizeof(int));
    int last_element = my_arraylen(completions) - 1;

    if (lines_info == NULL)
        return NULL;
    info[CHARS_INFO] += dprintf(1, "\n");
    for (int i = 0; completions[i] != NULL; ++i) {
        formated = format_arguments(completions[i], "/", "");
        if (formated == NULL)
            return NULL;
        reset_counter += 1;
        lines_info = is_reset(&reset_counter, offset, info, lines_info);
        lines_info[info[LINES_INFO]] =
            update_info(formated, i == last_element, i == completion_ptr, info);
    }
    info[WORDS_INFO] = my_arraylen(completions);
    return lines_info;
}
