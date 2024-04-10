/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** header for ll_parser
*/

#ifndef PARSING_H
    #define PARSING_H

    #include "env.h"
    #include <stdbool.h>
    #include <stddef.h>

static char const SPECIAL_CHARS[] = {
    '|',
    '&',
    ';',
    '<',
    '>',
    '\0'
};

typedef struct ll_node_s {
    char *value;
    int fds[2];
    bool (*func) (struct ll_node_s *self, env_t *env, int fd);
    bool is_operator;
    struct ll_node_s *right;
    struct ll_node_s *left;
} ll_node_t;

// symbols_handling.c
bool no_redir(ll_node_t *self, env_t *env, int);
bool pipe_redir(ll_node_t *self, env_t *env, int);

bool input_w_redir(ll_node_t *self, env_t *, int);
bool output_w_redir(ll_node_t *self, env_t *, int);
bool output_a_redir(ll_node_t *self, env_t *, int);
bool input_a_redir(ll_node_t *self, env_t *, int);

// ll_parser.c
ll_node_t *ll_parser(char *input);
bool lauch_command(ll_node_t *self, env_t *env, int fd);

typedef struct model_s {
    char *sep;
    bool (*exec_func) (struct ll_node_s *self, env_t *env, int fd);
} model_t;

static const model_t MODEL_SEP[] = {
    {";", no_redir},
    {"&&", NULL},
    {"||", NULL},
    {"&", NULL},
    {"|", pipe_redir},
    {"<<", input_a_redir},
    {"<", input_w_redir},
    {">>", output_a_redir},
    {">", output_w_redir},
    {NULL, NULL}
};

bool ischar_in_str(char c, const char *separators);
bool find_char_str(char const *str, char const *to_check);
int str_in_tab(char const *const *tab, char const *str);
bool str_contains(const char *str, const char *tocheck);


#endif
