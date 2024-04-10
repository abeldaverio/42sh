/*
** EPITECH PROJECT, 2024
** get env array
** File description:
** transform the list into an array
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "env.h"

static bool fill_the_array(char **array, env_list_t **env_list)
{
    int variable_size;
    int value_size;

    if (*env_list == NULL)
        return true;
    variable_size = strlen((*env_list)->variable);
    value_size = strlen((*env_list)->value);
    *array = calloc(sizeof(char), (variable_size + value_size + 2));
    if (*array == NULL)
        return false;
    strcpy(*array, (*env_list)->variable);
    (*array)[variable_size] = '=';
    strcpy(*array + variable_size + 1, (*env_list)->value);
    return fill_the_array(array + 1, &(*env_list)->next);
}

static int sizeof_list(env_list_t **env_list, int size)
{
    if (*env_list == NULL)
        return size;
    return sizeof_list(&(*env_list)->next, size + 1);
}

char **get_env_array(env_list_t **env_list)
{
    int size = sizeof_list(env_list, 0);
    char **array = calloc(sizeof(char *), (size + 1));

    if (array == NULL)
        return NULL;
    if (!fill_the_array(array, env_list))
        return NULL;
    array[size] = NULL;
    return array;
}
