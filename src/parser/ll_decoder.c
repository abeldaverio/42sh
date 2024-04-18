/*
** EPITECH PROJECT, 2024
** minish2
** File description:
** ll decoder
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "env.h"
#include "functions.h"
#include "ll_parsing.h"

void free_tree(ll_node_t *current)
{
    if (current == NULL)
        return;
    free_tree(current->left);
    free_tree(current->right);
    if (current != NULL) {
        free(current->value);
        free(current);
    }
}

static bool ll_real_decoder(env_t *env, ll_node_t *current)
{
    bool exit = false;

    if (current == NULL)
        return 0;
    if (current->func != NULL) {
        if (current->is_operator)
            exit = current->func(current, env, -1);
        else
            exit = current->func(current, env, -1);
    }
    return exit;
}

static bool check_node(ll_node_t *node)
{
    if (node == NULL)
        return false;
    if (node->func == NULL)
        return true;
    if (node->value[0] == '\n' || node->value[0] == '\0')
        return true;
    return false;
}

static bool ambiguouscheck(ll_node_t *current)
{
    if (current->value[0] != '>')
        return false;
    if (strcmp("|", current->right->value) == 0 ||
        strcmp(">", current->right->value) == 0) {
        return true;
    }
    return false;
}

static void ll_tester(ll_node_t *current, bool *err)
{
    if (current == NULL)
        return;
    if (check_node(current->right) || check_node(current->left)) {
        dprintf(STDERR_FILENO, "Invalid null command.\n");
        *err = true;
        return;
    }
    if (ambiguouscheck(current)) {
        dprintf(STDERR_FILENO, "Ambiguous output redirect.\n");
        *err = true;
        return;
    }
    if (current->func == NULL) {
        dprintf(STDERR_FILENO, "Invalid null command.\n");
        *err = true;
        return;
    }
    ll_tester(current->left, err);
    ll_tester(current->right, err);
}

static bool error_in_args(char **commands)
{
    ll_node_t *root = NULL;
    bool err = false;

    if (commands == NULL)
        return true;
    for (int i = 0; commands[i] != NULL; i++) {
        root = ll_parser(commands[i]);
        ll_tester(root, &err);
        free_tree(root);
        if (err == true) {
            return true;
        }
    }
    return false;
}

bool lauch_command(ll_node_t *self, env_t *env, int)
{
    char **input_twod = NULL;
    int return_value = 0;

    input_twod = format_arguments(self->value, " \t\n", "\"\'");
    if (format_input(&input_twod)) {
        env->last_return = 1;
        free_array(input_twod);
        return 1;
    }
    if (input_twod == NULL)
        return return_value;
    return_value = execute(input_twod, env);
    return return_value;
}

static bool pre_checking(char **commands, env_t *env)
{
    if (commands[0] == NULL) {
        free_array(commands);
        return false;
    }
    if (error_in_args(commands)) {
        env->last_return = 1;
        free_array(commands);
        return false;
    }
    return true;
}

int start_tree(env_t *env, char *input)
{
    ll_node_t *root = NULL;
    int return_value = 0;
    char **commands = NULL;

    commands = format_arguments(input, ";\n", "");
    if (!pre_checking(commands, env))
        return false;
    for (int i = 0; commands[i] != NULL; i++) {
        root = ll_parser(commands[i]);
        return_value = ll_real_decoder(env, root);
        free_tree(root);
    }
    free_array(commands);
    return return_value != true;
}
