/*
** EPITECH PROJECT, 2018
** arraylist
** File description:
** arraylist
*/

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#define ARRAY_MIN_SIZE 10
#define ARRAY_MAX_SIZE 2147483639

typedef struct arraylist_s {
    unsigned int size;
    unsigned int allocsize;
    void **list;
} arraylist_t;

arraylist_t *new_arraylist(int size);
void arraylist_add(arraylist_t *list, void *obj);
void *arraylist_remove(arraylist_t *list, unsigned int index);

#endif /* !ARRAYLIST_H_ */
