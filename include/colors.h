/*
** EPITECH PROJECT, 2024
** colors
** File description:
** colors characters
*/

#ifndef COLORS_H
    #define COLORS_H

static const char DEFAULT[] = "\033[0m";

typedef enum prompt_color_e {
    USERNAME = 0,
    HOST,
    DIR,
    SUCCESS,
    FAILURE,
    SYMBOL,
}prompt_color_t;

#endif
