/*
** EPITECH PROJECT, 2024
** print prompt
** File description:
** print the prompt
*/

#include <stdio.h>
#include <string.h>
#include "env.h"
#include "functions.h"
#include "colors.h"

static char *get_dir(char *pwd)
{
    int last_slash = 0;

    if (pwd == NULL)
        return NULL;
    for (int i = 0; pwd[i] != '\0'; i++)
        if (pwd[i] == '/')
            last_slash = (i == 0) ? i : i + 1;
    return pwd + last_slash;
}

void print_boring_prompt(char *username, char *version, char *dir, env_t *env)
{
    dprintf(1, "%s@", ((username == NULL) ? "" : username));
    dprintf(1, "%s:", ((version == NULL) ? "" : version));
    dprintf(1, "%s", ((dir == NULL) ? "" : dir));
    if (env->last_return == 0)
        dprintf(1, " > %ld ", env->last_return);
    else
        dprintf(1, " > %ld ", env->last_return);
    dprintf(1, "$> ");
}

static void print_formated_prompt(char *str,
    char *value, prompt_color_t color, char **colors)
{
    char color_buff[255] = {0};

    if ((my_arraylen(colors) > (int)color) && (strlen(colors[color]) < 255))
        sprintf(color_buff, "\033%s", colors[color]);
    dprintf(1, "%s", color_buff);
    dprintf(1, str, (value == NULL) ? "" : value);
    dprintf(1, "%s", DEFAULT);
}

static void print_formated_last_return(size_t last_return,
    prompt_color_t color, char **colors)
{
    char color_buff[255] = {0};

    if ((my_arraylen(colors) > (int)color) && (strlen(colors[color]) < 255))
        sprintf(color_buff, "\033%s", colors[color]);
    dprintf(1, " > %s%ld%s ", color_buff, last_return, DEFAULT);
}

char **get_colors(env_t *env)
{
    char **colors = get_formated_value("PROMPT_COLORS", env->env_list);

    return colors;
}

void print_cool_prompt(env_t *env, char *version, char *dir, char **colors)
{
    dprintf(1, "@");
    print_formated_prompt("%s", version, HOST, colors);
    dprintf(1, ":");
    print_formated_prompt("%s", dir, DIR, colors);
    if (env->last_return == 0) {
        print_formated_last_return(env->last_return, SUCCESS, colors);
    } else {
        print_formated_last_return(env->last_return, FAILURE, colors);
    }
    print_formated_prompt("%s", "$> ", SYMBOL, colors);
    free_array(colors);
}

void print_prompt(env_t *env)
{
    char *username = search_env_value("USER", env->env_list);
    char *version = search_env_value("HOSTNAME", env->env_list);
    char *dir = get_dir(search_env_value("PWD", env->env_list));
    char **colors = get_colors(env);

    if (colors == NULL) {
        print_boring_prompt(username, version, dir, env);
    } else {
        print_formated_prompt("%s", username, USERNAME, colors);
        print_cool_prompt(env, version, dir, colors);
    }
}
