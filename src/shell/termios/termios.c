/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** termios
*/

#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "complete.h"
#include "functions.h"
#include "macros.h"
#include "vector.h"
#include "env.h"
#include "prompt.h"
#include "special_chars.h"

static void init_termios(struct termios *term, struct termios *old_term)
{
    tcgetattr(0, old_term);
    memcpy(term, old_term, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, term);
}

void reset_autocompletion(prompt_t *prompt, env_t *env)
{
    char *save = NULL;

    if ((prompt->in_completion && prompt->character != '\t' && prompt->character != '\033') &&
        prompt->completion_candidate != NULL) {
        prompt->completion_ptr = 0;
        clear_last_completion(prompt);
        save = *prompt->line;
        *prompt->line = str_to_vector(prompt->completion_candidate);
        free(prompt->completion_candidate);
        prompt->completion_candidate = NULL;
        if (*prompt->line == NULL)
            *prompt->line = save;
        else
            vector_free(save);
        prompt->index = vector_total(*prompt->line);
        prompt->completion_ptr = 0;
        prompt->in_completion = false;
        print_input_line(prompt, env, true);
    }
}

static ssize_t switching(prompt_t *prompt, env_t *env)
{
    for (size_t i = 0; i < NB_OF_SPECIAL_INPUT; ++i) {
        if (prompt->character == SPECIAL_INPUT[i].character) {
            reset_autocompletion(prompt, env);
            return SPECIAL_INPUT[i].function(prompt, env);
        }
    }
    reset_autocompletion(prompt, env);
    if ((ssize_t)vector_total(*prompt->line) == prompt->index)
        vector_add(prompt->line, &prompt->character);
    else
        vector_push(prompt->line, prompt->index, &prompt->character);
    print_input_line(prompt, env, false);
    return prompt->index + 1;
}

size_t input_to_str(char **data, char **input, ssize_t index)
{
    vector_t *vector = (vector_t *)(*(void **)data - sizeof(vector_t));
    char *result = strndup(*data, vector->current);

    if (vector != NULL)
        free(vector);
    *input = result;
    return index;
}

static bool loop_char(prompt_t *prompt, env_t *env, char **input)
{
    while (true) {
        prompt->character = my_getchar();
        if (prompt->character == KEY_ENTER) {
            clear_last_completion(prompt);
            reset_autocompletion(prompt, env);
            dprintf(1, prompt->tty == 1 ? "\n" : "");
            return false;
        }
        prompt->index = switching(prompt, env);
        if (prompt->index == -1) {
            input_to_str(prompt->line, input, prompt->index);
            return true;
        }
    }
}

size_t display_changes(env_t *env, size_t prompt_size, char **input, int tty)
{
    prompt_t prompt = {0};
    struct termios term = {0};
    struct termios oldterm = {0};
    char *line = vector_init(sizeof(char));

    prompt.line = &line;
    prompt.prompt_size = prompt_size;
    prompt.tty = tty;
    check_free(*input);
    init_termios(&term, &oldterm);
    if (loop_char(&prompt, env, input) == true) {
        tcsetattr(0, TCSANOW, &oldterm);
        return -1;
    }
    tcsetattr(0, TCSANOW, &oldterm);
    return input_to_str(&line, input, prompt.index);
}
