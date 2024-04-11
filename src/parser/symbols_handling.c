/*
** EPITECH PROJECT, 2024
** mysh
** File description:
** symbols handling
*/

#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "ll_parsing.h"
#include "macros.h"
#include "functions.h"

static void execute_child(ll_node_t *self, int *fds, env_t *env)
{
    dup2(fds[IN], STDOUT_FILENO);
    close(fds[OUT]);
    self->left->func(self->left, env, -1);
    exit(env->last_return);
}

static void execute_parent(ll_node_t *self,
    int *fds, env_t *env, int stdin_save)
{
    dup2(fds[OUT], STDIN_FILENO);
    close(fds[IN]);
    self->right->func(self->right, env, -1);
    dup2(stdin_save, STDIN_FILENO);
}

bool pipe_redir(ll_node_t *self, env_t *env, int)
{
    int fds[2];
    pid_t pid = 0;
    int stat_val = 0;
    int stdin_save = dup(STDIN_FILENO);

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        execute_child(self, fds, env);
    } else {
        execute_parent(self, fds, env, stdin_save);
        waitpid(pid, &stat_val, 0);
    }
    update_status(stat_val, env);
    return true;
}

bool no_redir(ll_node_t *, env_t *, int)
{
    return true;
}
