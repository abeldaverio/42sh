/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** kay_tab
*/

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

static void clean_up_term(prompt_t *prompt, env_t *env, int *lines_info)
{
    dprintf(1, "\033[A");
    for (int i = 0; i <= prompt->last_completion_offset; i++) {
        dprintf(1, "\033[A");
        cursor_backward(lines_info[i]);
    }
    dprintf(1, "\33[2K");
    print_input_line(prompt, env, true);
}

static char *truncate_input(char *completion, char *old_completion, int offset)
{
    char *new_completion = calloc((strlen(completion) +
        strlen(old_completion)) - offset, sizeof(char));

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

void concat_vector(char *completion, prompt_t *prompt, env_t *env)
{
    char *old_completion = get_completion(*prompt->line);
    int offset = 0;
    char *new_completion = NULL;

    if (old_completion != NULL)
        offset = strlen(old_completion);
    if (offset != 0) {
        new_completion = truncate_input(completion, old_completion, offset);
    } else {
        new_completion = my_strcat(2, old_completion, completion);
    }
    if (new_completion == NULL)
        return;
    vector_free(*prompt->line);
    *prompt->line = vector_init(sizeof(char));
    if (*prompt->line == NULL)
        return;
    for (int i = 0; new_completion[i]; ++i) {
        vector_push(prompt->line, i, &new_completion[i]);
    }
    prompt->index = vector_total(*prompt->line);
    print_input_line(prompt, env, true);
}

void clear_last_completion(prompt_t *prompt)
{
    if (prompt->last_completion_offset != 0) {
        for (int i = 0; i <= prompt->last_completion_offset; i++) {
            dprintf(1, "\033[D");
            dprintf(1, "\33[2K");
        }
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
    clean_up_term(prompt, env, lines_info);
    if (prompt->completion_ptr != -1) {
        if (prompt->completion_candidate != NULL)
            free(prompt->completion_candidate);
        prompt->completion_candidate =
            get_completion_result(*prompt->line, prompt->completion_ptr);
    }
    prompt->completion_ptr += 1;
    if (info[WORDS_INFO] != 0)
        prompt->completion_ptr %= info[WORDS_INFO];
    free(lines_info);
    return prompt->index;
}
