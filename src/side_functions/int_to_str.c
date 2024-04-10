/*
** EPITECH PROJECT, 2024
** int to str
** File description:
** takes an int and and convert it into an string
*/

#include <stdlib.h>

static int get_int_size(int nb)
{
    int i;

    nb = (nb < 0) ? -nb : nb;
    for (i = 1; nb >= 10; i++)
        nb /= 10;
    return i;
}

static void fill_the_string(char *str, int nb, int nb_of_digits, int j)
{
    for (int i = 1; i <= nb_of_digits; i++) {
        str[nb_of_digits - i + j] = '0' + nb % 10;
        nb /= 10;
    }
    str[nb_of_digits + j] = '\0';
}

char *int_to_str(int nb)
{
    int nb_of_digits = get_int_size(nb);
    char *str;
    int j = 0;

    if (nb < 0) {
        str = malloc(sizeof(char) * (nb_of_digits + 2));
        if (str == NULL)
            return NULL;
        str[0] = '-';
        j++;
        nb = -nb;
    } else {
        str = malloc(sizeof(char) * (nb_of_digits + 1));
        if (str == NULL)
            return NULL;
    }
    fill_the_string(str, nb, nb_of_digits, j);
    return str;
}
