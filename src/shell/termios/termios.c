/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** termios
*/

#include <stdlib.h>
#include <sys/types.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
#include "macros.h"
#include "vector.h"
#include "env.h"
#include "prompt.h"

static void init_termios(struct termios *term, struct termios *old_term)
{
    tcgetattr(0, old_term);
    memcpy(term, old_term, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, term);
}

static size_t arrow(size_t index, char **line)
{
    char c = getchar();

    if (c != '[')
        return index;
    c = getchar();
    if (c == 'D' && index > 0) {
        cursor_backward(1);
        index--;
    }
    if (c == 'C' && index < vector_total(*line)) {
        cursor_forward(1);
        index++;
    }
    return index;
}

/* dprintf(1, "\33[%dF\n", index / 46); */
/* cursor_forward(index % 46 + 1); */
static void print_line(prompt_t *prompt, env_t *env)
{
    cursor_backward(prompt->prompt_size + prompt->index);
    dprintf(1, "\33[K");
    print_prompt(env);
    dprintf(1, "%.*s", (int)vector_total(*prompt->line), *prompt->line);
    cursor_backward(vector_total(*prompt->line));
    cursor_forward(prompt->index + 1);
}

// struct with c, index, line, prompt_size
static ssize_t switching(prompt_t *prompt, env_t *env)
{
    if (prompt->character == '\033')
        return arrow(prompt->index, prompt->line);
    if (prompt->character == 4)
        return -1;
    if (prompt->character == KEY_DEL) {
        prompt->index = delete_command(prompt->index, prompt->line);
        print_line(prompt, env);
        return prompt->index;
    } else if ((ssize_t)vector_total(*prompt->line) == prompt->index)
        vector_add(prompt->line, &prompt->character);
    else
        vector_push(prompt->line, prompt->index, &prompt->character);
    print_line(prompt, env);
    return prompt->index + 1;
}

static size_t vector_to_str(char **data, char **input, ssize_t index)
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
    while (1) {
        prompt->character = getchar();
        if (prompt->character == 0x000a) {
            write(1, "\n", 1);
            return false;
        }
        prompt->index = switching(prompt, env);
        if (prompt->index == -1) {
            vector_to_str(prompt->line, input, prompt->index);
            return true;
        }
    }
}

// handle is a tty
// prompt
size_t display_changes(env_t *env, size_t prompt_size, char **input)
{
    prompt_t prompt = {0};
    struct termios term = {0};
    struct termios oldterm = {0};
    char *line = vector_init(sizeof(char));

    prompt.line = &line;
    prompt.prompt_size = prompt_size;
    check_free(*input);
    init_termios(&term, &oldterm);
    loop_char(&prompt, env, input);
    tcsetattr(0, TCSANOW, &oldterm);
    return vector_to_str(&line, input, prompt.index);
}
