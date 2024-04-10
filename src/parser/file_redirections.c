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
#include <unistd.h>
#include <fcntl.h>

#include "functions.h"
#include "ll_parsing.h"

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
    return false;
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
    return false;
}

bool input_a_redir(ll_node_t *self, env_t *env, int)
{
    return 0;
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
    return false;
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
    return false;
}
