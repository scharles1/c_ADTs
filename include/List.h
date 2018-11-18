/** 
 * File: List.h
 * ------------------------------------------------------
 * Defines the interface for the list type. This implements the standard
 * ADT doubly linked list type.
 */

#ifndef LIST_H
#define LIST_H

#include "ADT_common.h"

/**
 * Type: list
 * ------------------------------------------------------
 * The intention with this type is to hide the internals of the vector struct
 * by defining the vector_implementation struct in the vector.c file. This 
 * requires clients to use the prescribed API
 */
typedef struct list_implementation list;

/**
 * Function: vector_init
 * Usage: vector *v = vector_init (sizeof(int), 10, NULL)
 * ------------------------------------------------------
 * Creates a new empty vector and returns a pointer to it.
 *
 * Asserts: zero elemsz, allocation failure
 * Assumes: cleanup fn is valid
 */
list *list_init (size_t elem_sz, size_t capacity_hint, elem_destroy_fn fn);

#endif /* LIST_H */