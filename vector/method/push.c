/*
** EPITECH PROJECT, 2019
** push
** File description:
** vector
*/

#include "../my_vector.h"

void vector_push(my_vector_t *vector, void *elem)
{
    vector->size += 1;
    if (vector->size == vector->alloc_size)
        *vector = vector_realloc(vector);
    vector->vector[vector->size - 1] = elem;
}

void vector_push_at(my_vector_t *vector, void *elem, int index)
{
    vector->size += 1;
    if (vector->size == vector->alloc_size)
        *vector = vector_realloc(vector);
    for (int i = index; i < vector->size; i++)
        vector->vector[i + 1] = vector->vector[i];
    vector->vector[index] = elem;
}