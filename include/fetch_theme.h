/*
** EPITECH PROJECT, 2024
** fetch_theme
** File description:
** fetch_theme
*/

#ifndef FETCH_THEME_H
    #define FETCH_THEME_H
    #include <stddef.h>

typedef enum fetch_model_e {
    CAMILLE,
    SIZE
} fetch_model_t;

typedef struct fetch_theme_s {
    char *filepath;
    char *color;
} fetch_theme_t;

static const fetch_theme_t FETCH_THEME[] = {
    {"assets/fetch_logo/camille.txt", "\033[38;2;6;178;255m"}
};

bool fetch_command(char **argv, env_t *env, fetch_model_t model);
char *create_buffer(char *filepath);
char **get_colors(env_t *env);

#endif /* !FETCH_THEME_H */
