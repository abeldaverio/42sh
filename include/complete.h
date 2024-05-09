/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** header for autocompletion
*/

#pragma once

#include <stddef.h>
#include "prompt.h"
#include "env.h"

#define BEG 0
#define END 1

static const size_t MAX_RANGE[] = {16, 32};
static const size_t MID_RANGE[] = {8, 15};
static const size_t SMALL_RANGE[] = {0, 7};
static const int CHARS_INFO = 0;
static const int LINES_INFO = 1;
static const int WORDS_INFO = 2;

int *auto_compete_cmd(char *complete, int completion_ptr, int info[3]);
int *auto_compete_dir(char *complete, int completion_ptr, int info[3]);
char *get_completion(char *input);
int *print_completion(char **completions, int completion_ptr, int info[3]);

char *auto_compete_dir_get(char *complete, int completion_ptr);
char *auto_compete_cmd_get(char *complete, int completion_ptr);
char *get_completion_result(char *input, int completion_ptr);
char *isolate_completion(char **candidates, int completion_ptr);

void clear_last_completion(prompt_t *prompt);
void reset_autocompletion(prompt_t *prompt, env_t *env);
