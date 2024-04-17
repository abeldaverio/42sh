/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** routes for file redir
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <threads.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "functions.h"
#include "ll_parsing.h"
#include "macros.h"

static bool error_in_open(int fd, char **formated, bool opening)
{
    if (fd == -1) {
        if (opening == true)
            dprintf(STDERR_FILENO, "%s: No such file or directory.\n",
            formated[0]);
        free_array(formated);
        return true;
    }
    free_array(formated);
    return true;
}

bool input_w_redir(ll_node_t *self, env_t *env, int)
{
    pid_t pid = 0;
    int stat_val = 0;
    char **formated = format_arguments(self->right->value, " \t", "");
    int fd = open(formated[0], O_RDONLY);

    if (error_in_open(fd, formated, true))
        return 1;
    pid = fork();
    if (pid == 0) {
        dup2(fd, STDIN_FILENO);
        self->left->func(self->left, env, fd);
        close(fd);
        exit(env->last_return);
    } else {
        waitpid(pid, &stat_val, 0);
    }
    update_status(stat_val, env);
    return true;
}

static bool compare_no_end(char *str, char *to_comp)
{
    if (strlen(str) - 1 != strlen(to_comp))
        return false;
    for (int i = 0; str[i] && str[i] != '\n'; i++) {
        if (str[i] != to_comp[i])
            return false;
    }
    return true;
}

static void execute_child(ll_node_t *self, int *fds, env_t *env)
{
    char **formated_val = format_arguments(self->right->value, "\t ", "");
    char *input = NULL;

    close(fds[OUT]);
    while (1) {
        request_input(&input, "? ");
        if (input == NULL || compare_no_end(input, formated_val[0])) {
            free(input);
            break;
        }
        dprintf(fds[IN], "%s", input);
    }
    free_array(formated_val);
    close(fds[IN]);
    exit(env->last_return);
}

static void execute_parent(ll_node_t *self,
    int *fds, env_t *env)
{
    int stdin_save = dup(STDIN_FILENO);

    dup2(fds[OUT], STDIN_FILENO);
    close(fds[IN]);
    self->left->func(self->left, env, -1);
    dup2(stdin_save, STDIN_FILENO);
    close(fds[OUT]);
}

bool input_a_redir(ll_node_t *self, env_t *env, int)
{
    int fds[2];
    pid_t pid = 0;
    int stat_val = 0;

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        execute_child(self, fds, env);
    } else {
        waitpid(pid, &stat_val, 0);
        execute_parent(self, fds, env);
    }
    update_status(stat_val, env);
    return true;
}

bool output_w_redir(ll_node_t *self, env_t *env, int)
{
    pid_t pid = 0;
    int stat_val = 0;
    char **formated = format_arguments(self->right->value, " \t", "");
    int fd = open(formated[0], O_TRUNC | O_CREAT | O_WRONLY, 0644);

    if (error_in_open(fd, formated, false))
        return 1;
    pid = fork();
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        self->left->func(self->left, env, fd);
        close(fd);
        exit(env->last_return);
    } else {
        waitpid(pid, &stat_val, 0);
    }
    update_status(stat_val, env);
    return true;
}

bool output_a_redir(ll_node_t *self, env_t *env, int)
{
    pid_t pid = 0;
    int stat_val = 0;
    char **formated = format_arguments(self->right->value, " \t", "");
    int fd = open(formated[0], O_APPEND | O_CREAT | O_WRONLY, 0644);

    if (error_in_open(fd, formated, false))
        return 1;
    pid = fork();
    if (pid == 0) {
        dup2(fd, STDOUT_FILENO);
        self->left->func(self->left, env, fd);
        close(fd);
        exit(env->last_return);
    } else {
        waitpid(pid, &stat_val, 0);
    }
    update_status(stat_val, env);
    return true;
}
