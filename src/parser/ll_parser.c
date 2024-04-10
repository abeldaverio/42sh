/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** ll decoder and executable
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ll_parsing.h"
#include "macros.h"

static char *alloc_str(int offset)
{
    char *str = malloc(sizeof(char) * (offset + 1));

    for (int i = 0; i < offset; i++)
        str[i] = 1;
    str[offset] = '\0';
    return str;
}

static char *str_clean_beg(char *str)
{
    int tot = 0;
    char *new = NULL;

    for (int i = 0; str[i] && (str[i] == ' ' || str[i] == '\t'); i++) {
        tot += 1;
    }
    new = malloc(sizeof(char) * (strlen(str) - tot));
    new[strlen(str) - tot] = '\0';
    for (int i = tot; str[i]; i++) {
        new[i - tot] = str[i];
    }
    return new;
}

static int offset_to_sep(char const *str,
    char const *separators, char const *first_address)
{
    int offset = 0;

    while (str != first_address && !ischar_in_str(*str, separators)) {
        offset -= 1;
        str--;
    }
    return offset;
}

static int sep_to_offset(char const *str,
    char const *separators, char const *first_address)
{
    int offset = 0;

    while (str != first_address && ischar_in_str(*str, separators)) {
        offset -= 1;
        str--;
    }
    return offset;
}

static char *format(char const *str, char const *first_address, int offset)
{
    char *new_str = NULL;

    if (first_address == (str + offset))
        offset -= 1;
    offset = ABS(offset);
    new_str = alloc_str(offset);
    for (int i = offset - 1; i >= 0; i--){
        new_str[i] = *str;
        str--;
    }
    return new_str;
}

static char *format_sep(char const *str,
    char const *separators, char const *first_address)
{
    char *new_str = NULL;
    int offset = sep_to_offset(str, separators, first_address);

    offset = ABS(offset);
    new_str = alloc_str(offset);
    for (int i = offset - 1; i >= 0; i--){
        new_str[i] = *str;
        str--;
    }
    return new_str;
}

static ll_node_t *init_node(char *cmd)
{
    ll_node_t *node = malloc(sizeof(ll_node_t));
    char *new = str_clean_beg(cmd);

    *(node) = (ll_node_t) {0};
    node->value = new;
    free(cmd);
    return node;
}

static bool get_func(ll_node_t *current)
{
    for (int i = 0; MODEL_SEP[i].sep != NULL; i++)
        if (strcmp(MODEL_SEP[i].sep, current->value) == 0) {
            current->func = MODEL_SEP[i].exec_func;
            return true;
        }
    current->func = lauch_command;
    if (ischar_in_str(current->value[0], "|&<>"))
        current->func = NULL;
    return false;
}

static void ll_filler(char *cmd, ll_node_t **head)
{
    ll_node_t *temp = *head;
    ll_node_t *node = init_node(cmd);

    if (*head == NULL){
        get_func(node);
        *head = node;
        return;
    }
    if (get_func(node)) {
        node->right = temp;
        node->is_operator = true;
        *head = node;
    } else {
        (*head)->left = node;
    }
}

ll_node_t *ll_parser(char *input)
{
    ll_node_t *first_node = NULL;
    char const *first_add = input;
    int offset = 0;

    input += strlen(input) - 1;
    while (input != first_add) {
        offset = offset_to_sep(input, SPECIAL_CHARS, first_add);
        if (ischar_in_str(*input, SPECIAL_CHARS)) {
            ll_filler(format_sep(input, SPECIAL_CHARS,
                first_add), &first_node);
            input += sep_to_offset(input, SPECIAL_CHARS, first_add);
        } else {
            ll_filler(format(input, first_add, offset), &first_node);
            input += offset;
        }
    }
    return first_node;
}
