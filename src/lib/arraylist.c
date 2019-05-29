/*
** EPITECH PROJECT, 2018
** ArrayList
** File description:
** ArrayList
*/

#include "arraylist.h"
#include <stdlib.h>
#include <stdio.h>

arraylist_t *new_arraylist(int size)
{
    arraylist_t *list = malloc(sizeof(arraylist_t));

    if (size <= 0) {
        list->allocsize = ARRAY_MIN_SIZE;
        list->size = 0;
        list->list = malloc(sizeof(void *) * list->allocsize);
    } else {
        list->allocsize = size;
        list->size = 0;
        list->list = malloc(sizeof(void *) * size);
    }
    if (list->list == 0) {
        free(list);
        return (0);
    }
    return (list);
}

void arraylist_grow(arraylist_t *list, int minSize)
{
    unsigned int nallocsize = 0;
    void **newlist = NULL;

    if (list != NULL) {
        nallocsize = list->allocsize + ((list->allocsize + 1) >> 1);
        if ((int)nallocsize - minSize < 0)
            nallocsize = minSize;
        if (nallocsize > ARRAY_MAX_SIZE)
            nallocsize = 2147483647;
        newlist = malloc(sizeof(void *) * nallocsize);
        if (newlist == NULL)
            return;
        for (unsigned int i = 0; i < list->size; i++)
            newlist[i] = list->list[i];
        free(list->list);
        list->list = newlist;
        list->allocsize = nallocsize;
    }
}

void arraylist_add(arraylist_t *list, void *obj)
{
    if (list != NULL) {
        if (list->size + 1 > list->allocsize)
            arraylist_grow(list, list->size + 1);
        if (list->size + 1 <= list->allocsize) {
            list->list[list->size] = obj;
            list->size += 1;
        }
    }
}

void *arraylist_remove(arraylist_t *list, unsigned int index)
{
    void *obj = NULL;

    if (list != NULL && index < list->size) {
        obj = list->list[index];
        for (unsigned int i = index + 1; i < list->size; i++)
            list->list[i - 1] = list->list[i];
        list->list[list->size - 1] = NULL;
        list->size -= 1;
        return (obj);
    }
    return (0);
}
