/*
** EPITECH PROJECT, 2019
** process_globings
** File description:
** process_globings
*/

#include "exec.h"
#include <glob.h>

void add_globings(arraylist_t *list, char *str)
{
    glob_t globbuf;
    int count = 0;

    globbuf.gl_offs = 0;
    glob(str, GLOB_DOOFFS | GLOB_BRACE, NULL, &globbuf);
    for (unsigned int i = 0; globbuf.gl_pathv[i]; i++) {
        count += 1;
        arraylist_add(list, globbuf.gl_pathv[i]);
    }
    if (count == 0) {
        arraylist_add(list, str);
    } else {
        free(str);
    }
}

char **process_globings(char **command)
{
    arraylist_t *final = new_arraylist(1);
    char **list = 0;

    for (int i = 0; command[i]; i++)
        add_globings(final, command[i]);
    arraylist_add(final, NULL);
    list = (char **)&final->list[0];
    free(command);
    free(final);
    return (list);
}