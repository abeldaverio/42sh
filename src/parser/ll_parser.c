/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** ll decoder and executable
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "ll_parsing.h"

static ll_node_t *init_node(char *cmd)
{
    ll_node_t *node = calloc(sizeof(ll_node_t), 1);

    node->value = strdup(cmd);
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
    char **formated = format_arguments(input, "\1", "");

    for (int i = my_arraylen(formated) - 1; i >= 0; i--) {
        if (formated[i] != NULL)
            ll_filler(formated[i], &first_node);
    }
    free_array(formated);
    return first_node;
}
