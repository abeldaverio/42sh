/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** key_up
*/

#include "env.h"
#include "prompt.h"
#include "vector.h"
#include "functions.h"
#include "complete.h"

void up_arrow_command(prompt_t *prompt, env_t *env)
{
    reset_autocompletion(prompt, env);
    if (env->history == NULL || prompt->in_completion)
        return;
    vector_free(*prompt->line);
    *prompt->line = vector_init(sizeof(char));
    if (*prompt->line == NULL)
        return;
    for (int i = 0; env->history->command[i]; ++i) {
        vector_push(prompt->line, i, &env->history->command[i]);
    }
    prompt->index = vector_total(*prompt->line);
    print_input_line(prompt, env, true);
    if (env->history->next == NULL)
        return;
    env->history = env->history->next;
}
