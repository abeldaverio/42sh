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

static int get_char(struct termios *term, struct termios *oterm)
{
    int character = 0;

    tcgetattr(0, oterm);
    memcpy(term, oterm, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, term);
    character = getchar();
    tcsetattr(0, TCSANOW, oterm);
    return character;
}

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
static void print_line(char **line, size_t prompt_size, size_t index,
    env_t *env)
{
    cursor_backward(prompt_size + index);
    dprintf(1, "\33[K");
    print_prompt(env);
    dprintf(1, "%.*s", vector_total(*line), *line);
    cursor_backward(vector_total(*line));
    cursor_forward(index + 1);
}

static ssize_t switching(char c, size_t index, char **line, env_t *env,
    size_t prompt_size)
{
    if (c == '\033')
        return arrow(index, line);
    if (c == 4)
        return -1;
    if (c == KEY_DEL) {
        index = delete_command(index, line);
        print_line(line, prompt_size, index, env);
        return index;
    } else if (vector_total(*line) == index)
        vector_add(line, &c);
    else
        vector_push(line, index, &c);
    print_line(line, prompt_size, index, env);
    return index + 1;
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

size_t display_changes(env_t *env, size_t prompt_size, char **input)
{
    int character = 0;
    struct termios term = {0};
    struct termios oldterm = {0};
    ssize_t index = 0;
    char *line = vector_init(sizeof(char));

    if (*input != NULL)
        free(*input);
    init_termios(&term, &oldterm);
    while (1) {
        character = getchar();
        if (character == 0x000a) {
            write(1, "\n", 1);
            break;
        }
        index = switching(character, index, &line, env, prompt_size);
        if (index == -1)
            return vector_to_str(&line, input, index);
    }
    tcsetattr(0, TCSANOW, &oldterm);
    return vector_to_str(&line, input, index);
}
