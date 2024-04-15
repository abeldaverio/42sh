/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** termios
*/

#include <termios.h>
#include <stdio.h>
#include <string.h>
#include "macros.h"

static struct termios term, oterm;

static void cursorforward(int x)
{
    printf("\033[%dC", (x));
}

static void cursorbackward(int x)
{
    printf("\033[%dD", (x));
}

int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) 
        ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}
static int kbesc(void)
{
    int c;

    if (!kbhit()) 
        return KEY_ESCAPE;
    c = getch();
    if (c == '[') {
        switch (getch()) {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_LEFT;
                break;
            case 'D':
                c = KEY_RIGHT;
                break;
            default:
                c = 0;
                break;
        }
    } else {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

static int kbget()
{
    int c;

    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

int display_changes(void)
{
    int c;

    while (1) {
        c = kbget();
        if (c == KEY_ENTER || c == KEY_ESCAPE || c == KEY_UP || c == KEY_DOWN) {
            break;
        } else
        if (c == KEY_RIGHT) {
            cursorbackward(1);
        } else
        if (c == KEY_LEFT) {
            cursorforward(1);
        } else {
            putchar(c);
        }
    }
    printf("\n");
    return 0;
}