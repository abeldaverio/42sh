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
#include <strings.h>
#include "arrows.h"
#include "complete.h"
#include "functions.h"
#include "prompt.h"
#include "env.h"
#include "macros.h"
#include "vector.h"

static char *truncate_input(prompt_t *prompt, char *completion, int offset)
{
    char *tmp = vector_to_str((void **)prompt->line);
    char *result = NULL;
    int tmplen = strlen(tmp);

    if (tmp == NULL)
        return NULL;
    for (int i = 0; i < offset + 1; i++) {
        tmp[tmplen - i] = '\0';
    }
    result = my_strcat(2, tmp, completion);
    free(tmp);
    return result;
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
        new_completion = truncate_input(prompt,
            completion, offset);
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

static void handle_cmplt_ptr(prompt_t *prompt, int offset, int info[3])
{
    if (prompt->completion_ptr + offset < 0) {
        prompt->completion_ptr = info[WORDS_INFO] - 1;
        return;
    }
    if (prompt->completion_ptr + offset >= info[WORDS_INFO]) {
        prompt->completion_ptr = 0;
        return;
    }
    prompt->completion_ptr += offset;
}

int handle_tab_completion(prompt_t *prompt, env_t *env, int offset)
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
    handle_cmplt_ptr(prompt, offset, info);
    free(lines_info);
    return prompt->index;
}

int handle_tab(prompt_t *prompt, env_t *env)
{
    char tab = '\t';

    if (prompt->tty != 1) {
        vector_push(prompt->line, prompt->index, &tab);
        prompt->index += 1;
        return prompt->index;
    }
    return handle_tab_completion(prompt, env, 1);
}
