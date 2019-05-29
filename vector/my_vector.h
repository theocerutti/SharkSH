/*
** EPITECH PROJECT, 2019
** dynamic_vector
** File description:
** code
*/

#ifndef my_vector_H_
#define my_vector_H_

#include <stdlib.h>
#include <stdio.h>

#define MIN_SIZE 10

typedef struct my_vector_s {
    int (*get_size)(struct my_vector_s *);

    void (*push)(struct my_vector_s *, void *);
    void (*push_at)(struct my_vector_s *, void *, int);

    void (*clear_v)(struct my_vector_s *);
    void (*pop)(struct my_vector_s *);
    void (*pop_at)(struct my_vector_s *, int);

    int size;
    int alloc_size;
    void **vector;
} my_vector_t;

#include "method/method.h"

#endif /* !my_vector_H_ */
