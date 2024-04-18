/*
** EPITECH PROJECT, 2023
** side functions
** File description:
** does put things
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>

static size_t get_allocate_size(size_t n_of_words, va_list list)
{
    size_t to_allocate = 0;
    char *word = NULL;

    for (size_t i = 0; i != n_of_words; i++) {
        word = va_arg(list, char *);
        if (word != NULL)
            to_allocate += strlen(word);
    }
    va_end(list);
    return to_allocate;
}

static int fill_word(char *new_buff, va_list list)
{
    char *to_copy = va_arg(list, char *);
    size_t offset = 0;

    if (to_copy == NULL)
        return -1;
    for (int i = 0; to_copy[i]; i++) {
        *new_buff = to_copy[i];
        new_buff++;
        offset += 1;
    }
    return offset;
}

char *my_strcat(size_t n_of_words, ...)
{
    va_list list;
    va_list list_counter;
    char *new_buff = NULL;
    char *new_copy = NULL;
    size_t to_allocate = 0;

    va_start(list, n_of_words);
    va_copy(list_counter, list);
    to_allocate = get_allocate_size(n_of_words, list_counter);
    new_buff = calloc(sizeof(char), (to_allocate + 1));
    new_copy = new_buff;
    for (size_t i = 0; i != n_of_words; i++) {
        new_buff += fill_word(new_buff, list);
    }
    va_end(list);
    return new_copy;
}
