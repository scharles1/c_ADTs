/** 
 * File: vector.h
 * ------------------------------------------------------
 * Defines the interface for the vector type.
 */

#ifndef VECTOR_H
#define VECTOR_H

/**
 * Type: vector
 * ------------------------------------------------------
 */
typedef struct vector_implementation vector;

/**
 * Type: elem_destroy_fn
 * ------------------------------------------------------
 */
typedef void (*elem_destroy_fn) (void *addr);

/**
 * Function: vector_init
 * Usage: vector *v = vector_init (sizeof(int), 10, NULL)
 * ------------------------------------------------------
 * Creates a new empty vector and returns a pointer to it.
 *
 * Asserts: zero elemsz, allocation failure
 * Assumes: cleanup fn is valid
 */
vector *vector_init (size_t elem_sz, size_t capacity_hint, elem_destroy_fn fn);

/**
 * Function: vector_destroy
 * Usage: vector_destroy (v)
 * ------------------------------------------------------
 * Destroys and frees all memory associated with vector
 */
void vector_destroy (vector *v);

/**
 * Function: vector_size
 * Usage: size_t size = vector_size (v)
 * ------------------------------------------------------
 * Returns the number of elements in the vector. Not necessarily equal to the
 * storage capacity of the vector
 */
size_t vector_size (vector *v);

/**
 * Function: vector_elem
 * Usage: void *elem = vector_elem (v, 0)
 * ------------------------------------------------------
 * Returns a pointer to the element in the vector defined by index. 
 */
void *vector_elem (vector *v, int index);

/**
 * Function: vector_insert
 * Usage: vector_insert (v, &elem, 0)
 * ------------------------------------------------------
 * Inserts the data pointed to by elem into the vector at the defined index.
 * This is done by copy.
 */
void vector_insert (vector *v, const void *elem, int index);

/**
 * Function: vector_append
 * Usage: vector_append (v, &elem)
 * ------------------------------------------------------
 * Appends the data pointed to by elem into the vector at the end. This is done
 * by copy. 
 */
void vector_insert (vector *v, const void *elem);

/**
 * Function: vector_replace
 * Usage: vector_replace (v, &elem, 0)
 * ------------------------------------------------------
 * Replaces the data at the index with the data pointed to by elem. This is done
 * by copy.
 */
void vector_replace (vector *v, const void *elem, int index);

#endif /* VECTOR_H */