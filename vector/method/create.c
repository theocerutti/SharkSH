/*
** EPITECH PROJECT, 2019
** init vector
** File description:
** code
*/

#include "../my_vector.h"

my_vector_t vector_realloc(my_vector_t *vector)
{
    my_vector_t new = vector_create(vector->alloc_size * 2);

    new.size = vector->size;
    new.alloc_size = vector->alloc_size * 2;
    new.vector = malloc(sizeof(void *) * new.alloc_size);
    for (int i = 0; i < new.size; i++)
        new.vector[i] = vector->vector[i];
    free(vector->vector);
    return (new);
}

void init_pointers(my_vector_t *vector)
{
    vector->get_size = &vector_get_size;
    vector->push = &vector_push;
    vector->push_at = &vector_push_at;
    vector->clear_v = &vector_clear;
    vector->pop = &vector_pop;
    vector->pop_at = &vector_pop_at;
}

my_vector_t vector_create(int size)
{
    my_vector_t new_vector;

    init_pointers(&new_vector);
    new_vector.size = 0;
    if (size <= 0) {
        new_vector.vector = malloc(sizeof(void *) * MIN_SIZE);
        new_vector.alloc_size = MIN_SIZE;
    } else {
        new_vector.vector = malloc(sizeof(void *) * size);
        new_vector.alloc_size = size;
    }
    return (new_vector);
}