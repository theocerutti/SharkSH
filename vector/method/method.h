/*
** EPITECH PROJECT, 2019
** method vector
** File description:
** code
*/

#ifndef METHOD_H_
#define METHOD_H_

#include "../my_vector.h"

my_vector_t vector_create(int size);
my_vector_t vector_realloc(my_vector_t *vector_to_realloc);

/*
** vector utils
*/

int vector_get_size(my_vector_t *vector);

/*
** Add element in vector
*/

void vector_push(my_vector_t *vector, void *elem);
void vector_push_at(my_vector_t *vector, void *elem, int index);

/*
** Delete element in vector
*/

void vector_clear(my_vector_t *vector);
void vector_pop(my_vector_t *vector);
void vector_pop_at(my_vector_t *vector, int index);

#endif /* !METHOD_H_ */
