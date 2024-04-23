/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** header for autocompletion
*/

#pragma once

#include <stddef.h>

#define BEG 0
#define END 1

static const size_t MAX_RANGE[] = {16, 32};
static const size_t MID_RANGE[] = {8, 15};
static const size_t SMALL_RANGE[] = {0, 7};

int auto_compete_cmd(char *complete);
int auto_compete_dir(char *complete);
char *get_completion(char *input);
int print_completion(char **completions);
