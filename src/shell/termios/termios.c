/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** termios
*/

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "macros.h"

int get_char(struct termios *term, struct termios *oterm) 
{
    int character = 0;

    tcgetattr(0, oterm);
    memcpy(term, oterm, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, term);
    character = getchar();
    tcsetattr(0, TCSANOW, oterm);
    return character;
}

static int keyboard_hit(struct termios *term, struct termios *oterm)
{
    int character = 0;

    tcgetattr(0, oterm);
    memcpy(term, oterm, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 0;
    term->c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, term);
    character = getchar();
    tcsetattr(0, TCSANOW, oterm);
    if (character != -1) 
        ungetc(character, stdin);
    return ((character != -1) ? 1 : 0);
}
static int keyboard_esc(struct termios *term, struct termios *oterm)
{
    int character = 0;

    character = get_char(term, oterm);
    if (character == '[') {
        switch (get_char(term, oterm)) {
            case 'A':
                character = KEY_UP;
                break;
            case 'B':
                character = KEY_DOWN;
                break;
            case 'C':
                character = KEY_LEFT;
                break;
            case 'D':
                character = KEY_RIGHT;
                break;
            case 'E':
                character = KEY_DEL;
                break;
            default:
                character = 0;
                break;
        }
    } else {
        character = 0;
    }
   if (character == 0)
       while (keyboard_hit(term, oterm)) {
           printf("kbhit\n");
           get_char(term, oterm);
           keyboard_esc(term, oterm);
       }
    return character;
}

static int keyboard_get(struct termios *term, struct termios *oterm)
{
    int character = 0;
    int res = 0;

    character = get_char(term, oterm);
    res = keyboard_esc(term, oterm);
    return (character == KEY_ESCAPE) ? res : character;
}

void init_termios(struct termios *term, struct termios *old_term)
{
    tcgetattr(0, old_term);
    memcpy(term, old_term, sizeof(struct termios));
    term->c_lflag &= ~(ICANON | ECHO);
    term->c_cc[VMIN] = 1;
    term->c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, term);
}

int is_command(struct termios *term, struct termios *oldterm)
{
    int car = 0;
    
    car = getchar();
    if (car == 27)
        return keyboard_esc(term, oldterm);
}

int display_changes(void)
{
    int character = 0;
    struct termios term = {0};
    struct termios oldterm = {0};
    char *line = NULL;
    char car = {0};

    init_termios(&term, &oldterm);
    character = is_command(&term, &oldterm);
    for (int i = 0; tab[i].flags != 0; i++)
        if (character == tab[i].flags)
            tab[i].d_f(line);
    tcsetattr(0, TCSANOW, &oldterm);
    while (read(0, &car, 1) != -1)
        dprintf(1, "%c", car);
//        printf("passé\n");
//        character = keyboard_get(&term, &oldterm);
//        for (int i = 0; tab[i].flags != 0; i++) {
//            if (character == tab[i].flags)
//                tab[i].d_f(line);
//        }
//    tcsetattr(0, TCSANOW, &oldterm);
//    }
    return 1;
}