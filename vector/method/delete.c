/*
** EPITECH PROJECT, 2019
** delete vector elem
** File description:
** code
*/

#include "../my_vector.h"

void vector_clear(my_vector_t *vector)
{
    void **new = malloc(sizeof(void *) * vector->alloc_size);

    for (int i = 0; i < vector->size; i++)
        free(vector->vector[i]);
    free(vector->vector);
    vector->size = 0;
    vector->vector = new;
}

void vector_pop(my_vector_t *vector)
{
    void **new = malloc(sizeof(void *) * vector->alloc_size);

    if (vector->size == 0)
        return;
    else {
        vector->size -= 1;
        for (int i = 0; i < vector->size; i++)
            new[i] = vector->vector[i];
        free(vector->vector);
        vector->vector = new;
    }
}

void vector_pop_at(my_vector_t *vector, int index)
{
    void **new = malloc(sizeof(void *) * vector->alloc_size);

    if (vector->size == 0 || index >= vector->size)
        return;
    else {
        vector->size -= 1;
        for (int i = 0; i < index; i++)
            new[i] = vector->vector[i];
        for (int i = index; i < vector->size; i++)
            new[i] = vector->vector[i + 1];
        free(vector->vector);
        vector->vector = new;
    }
}