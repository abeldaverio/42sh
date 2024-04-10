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

bool pipe_redir(ll_node_t *self, env_t *env, int)
{
    int fds[2];
    pid_t pid = 0;
    int stat_val = 0;
    int stdin_save = dup(STDIN_FILENO);

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        dup2(fds[IN], STDOUT_FILENO);
        close(fds[OUT]);
        self->left->func(self->left, env, -1);
        exit(env->last_return);
    } else {
        dup2(fds[OUT], STDIN_FILENO);
        close(fds[IN]);
        self->right->func(self->right, env, -1);
        dup2(stdin_save, STDIN_FILENO);
        waitpid(pid, &stat_val, 0);
    }
    update_status(stat_val, env);
    return false;
}

bool no_redir(ll_node_t *, env_t *, int)
{
    return 0;
}
