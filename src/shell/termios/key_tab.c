/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** kay_tab
*/

#include <bits/posix2_lim.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrows.h"
#include "complete.h"
#include "functions.h"
#include "prompt.h"
#include "env.h"
#include "macros.h"
#include "vector.h"

static char *truncate_input(char *completion, char *old_completion, int offset)
{
    char *new_completion = calloc((strlen(completion) +
        strlen(old_completion) + 1) - offset, sizeof(char));

    if (new_completion == NULL)
        return NULL;
    for (size_t i = 0; i < strlen(old_completion) - offset; i++) {
        new_completion[i] = old_completion[i];
    }
    for (size_t i = 0; completion[i]; i++) {
        new_completion[i + (strlen(old_completion) - offset)] = completion[i];
    }
    return new_completion;
}

static char *get_new_completion(prompt_t *prompt, char *completion)
{
    char *tmp = vector_to_str((void **)prompt->line);
    char *result = NULL;

    if (tmp == NULL)
        return NULL;
    result = my_strcat(2, tmp, completion);
    free(tmp);
    return result;
}

char *concat_vector(prompt_t *prompt)
{
    char *completion = get_completion_result(*prompt->line,
        prompt->completion_ptr);
    char *old_completion = get_completion(*prompt->line);
    int offset = 0;
    char *new_completion = NULL;

    if (old_completion != NULL)
        offset = strlen(old_completion);
    if (offset != 0) {
        new_completion = truncate_input(completion, old_completion, offset);
    } else {
        new_completion = get_new_completion(prompt, completion);
    }
    free(completion);
    free(old_completion);
    return new_completion;
}

static void reset_lines(prompt_t *prompt, env_t *env, int *lines_info)
{
    dprintf(1, "\33[A");
    for (int i = 0; i <= prompt->last_completion_offset; i++) {
        dprintf(1, "\33[A");
        cursor_backward(lines_info[i]);
    }
    dprintf(1, "\33[2K");
    if (prompt->completion_candidate == NULL) {
        print_input_line(prompt, env, true);
        return;
    }
}

static void clean_up_term(prompt_t *prompt, env_t *env, int *lines_info)
{
    char *tmp = NULL;
    char *save = NULL;

    reset_lines(prompt, env, lines_info);
    tmp = str_to_vector(prompt->completion_candidate);
    if (tmp == NULL)
        return;
    save = *prompt->line;
    prompt->index = vector_total(tmp);
    *prompt->line = tmp;
    print_input_line(prompt, env, true);
    *prompt->line = save;
    prompt->index = vector_total(*prompt->line);
    vector_free(tmp);
}

void clear_last_completion(prompt_t *prompt)
{
    if (prompt->last_completion_offset == 0)
        return;
    for (int i = 0; i <= prompt->last_completion_offset; i++) {
        dprintf(1, "\33[B");
        dprintf(1, "\33[2K");
    }
    for (int i = 0; i <= prompt->last_completion_offset; i++) {
        dprintf(1, "\33[A");
    }
}

int handle_tab(prompt_t *prompt, env_t *env)
{
    int info[3] = {0};
    int *lines_info = NULL;

    clear_last_completion(prompt);
    lines_info = auto_complete(*prompt->line, prompt->completion_ptr, info);
    prompt->last_completion_offset = info[LINES_INFO];
    prompt->in_completion = true;
    if (lines_info == NULL)
        return 0;
    if (prompt->completion_ptr != -1) {
        if (prompt->completion_candidate != NULL)
            free(prompt->completion_candidate);
        prompt->completion_candidate = concat_vector(prompt);
    }
    clean_up_term(prompt, env, lines_info);
    prompt->completion_ptr += 1;
    if (info[WORDS_INFO] != 0)
        prompt->completion_ptr %= info[WORDS_INFO];
    free(lines_info);
    return prompt->index;
}
