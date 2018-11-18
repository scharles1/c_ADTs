/** 
 * File: Vector.h
 * ------------------------------------------------------
 * Defines the interface for the vector type. This implements the standard
 * ADT vector that acts as a resizeable array.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include "ADT_common.h"
#include "ADT_private_implementations.h"

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
 *
 * Asserts: null pointer
 * Assumes: valid initialized vector pointer
 */
void vector_destroy (vector *v);

/**
 * Function: vector_size
 * Usage: size_t size = vector_size (v)
 * ------------------------------------------------------
 * Returns the number of elements in the vector. Not necessarily equal to the
 * storage capacity of the vector
 *
 * Asserts: null pointer
 * Assumes: valid initialized vector pointer
 */
size_t vector_size (const vector *v);

/**
 * Function: vector_access
 * Usage: void *elem = vector_access (v, 0)
 * ------------------------------------------------------
 * Returns a pointer to the element in the vector defined by index. 
 *
 * Asserts: null pointer
 * Assumes: valid initialized vector pointer
 *          valid index (index checking is left to the client's responsibility)
 */
void *vector_access (vector *v, int index);

/**
 * Function: vector_insert
 * Usage: vector_insert (v, &elem, 0)
 * ------------------------------------------------------
 * Inserts the data pointed to by elem into the vector at the defined index.
 * This is done by copy. All elements after index are shifted back by one.
 *
 * Asserts: null pointer (v, or elem), valid index
 * Assumes: valid initialized vector pointer
 *          valid elem pointer with data to copy into vector
 */
void vector_insert (vector *v, const void *elem, int index);

/**
 * Function: vector_remove
 * Usage: vector_remove (v, 0)
 * ------------------------------------------------------
 * Removes the element at index and shifts remaining elements down to fill the
 * empty element. The element is destroyed with the provided destroy function.
 */
void vector_remove (vector *v, int index);

/**
 * Function: vector_append
 * Usage: vector_append (v, &elem)
 * ------------------------------------------------------
 * Appends the data pointed to by elem into the vector at the end. This is done
 * by copy.
 *
 * Asserts: null pointer (v, or elem)
 * Assumes: valid initialized vector pointer
 *          valid elem pointer with data to copy into vector
 */
void vector_append (vector *v, const void *elem);

/**
 * Function: vector_replace
 * Usage: vector_replace (v, &elem, 0)
 * ------------------------------------------------------
 * Replaces the data at the index with the data pointed to by elem. This is done
 * by copy.
 */
void vector_replace (vector *v, const void *elem, int index);

/**
 * Function: vector_clear
 * Usage: vector_clear (v)
 * ------------------------------------------------------
 * Clears the vector and destroys all internal contents 
 */
void vector_clear (vector *v);

/**
 * Function: vector_search
 * Usage: void *ptr = vector_search (v, &elem, cmp_func)
 * ------------------------------------------------------
 * Searches the vector for an element that matches the data pointed to by key.
 * The sorted variable controls the search method. If the vector is sorted, a 
 * binary search is used. Otherwise a linear search is used.
 */
void *vector_search (const vector *v, const void *key, compare_fn fn, bool sorted);

/**
 * Function: vector_sort
 * Usage: vector_sort (v, cmp_func)
 * ------------------------------------------------------
 * Searches the vector for an element that matches the data pointed to by key.
 * The sorted variable controls the search method. If the vector is sorted, a 
 * binary search is used. Otherwise a linear search is used.
 */
void vector_sort (vector *v, compare_fn fn);

#endif /* VECTOR_H */