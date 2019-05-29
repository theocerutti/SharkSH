/*
** EPITECH PROJECT, 2019
** spliter
** File description:
** spliter
*/

#include <unistd.h>
#include <stdlib.h>
#include "arraylist.h"

int contain(const char *txt, const char *sep)
{
    int len = -1;

    while (sep[++len]);
    for (int i = 0; txt[i] && sep[i] && i < len; i++) {
        if (txt[i] != sep[i])
            return (0);
    }
    return (1);
}

int get_word(const char *txt, const char *sep, int start)
{
    int end = 0;

    while (txt[start + end] && !contain(txt + start + end, sep)) {
        end += 1;
    }
    return (end);
}

char *cut(const char *txt, int start, int end)
{
    char *new_txt = 0;
    int len = end-start;

    if (len <= 0) {
        new_txt = malloc(sizeof(char));
        new_txt[0] = 0;
        return (new_txt);
    } else {
        new_txt = malloc(sizeof(char) * (len + 1));
        for (int i = start; i < end; i++) {
            new_txt[i - start] = txt[i];
        }
        new_txt[end - start] = 0;
        return (new_txt);
    }
}

arraylist_t *split(const char *txt, const char *sep)
{
    int len = 0;
    int start = 0;
    int seplen = -1;
    int txtlen = -1;
    arraylist_t *list = new_arraylist(0);

    while (txt[++txtlen]);
    while (sep[++seplen]);
    while (start < txtlen) {
        len = get_word(txt, sep, start);
        arraylist_add(list, cut(txt, start, start + len));
        start += len + seplen;
    }
    return (list);
}
