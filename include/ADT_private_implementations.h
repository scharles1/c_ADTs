/** 
 * File: ADT_private_implementations.h
 * ------------------------------------------------------
 * Header file that contains implementation of ADT objects. This is considered
 * private and should not be used by the client in any way.
 */

#ifndef ADT_PRIVATE_IMPLEMENTATIONS_H
#define ADT_PRIVATE_IMPLEMENTATIONS_H

/**
 * Vector Implementations
 * ------------------------------------------------------------------------- 
 */

/**
 * Struct: vector
 * ----------------------------------
 * The private vector implementation
 *
 * field elems        - the start of the array of elements
 * field capacity     - the current number of elements the vector can hold
 * field elem_sz      - the size of elements in bytes the vector stores
 * field n_elems      - the current number of elements stored in the vector
 * field elem_destroy - the function to call on the vector elements to destroy
 *                       on clean up
 */
typedef struct
{
	void *elems;
	size_t capacity;
	size_t elem_sz;
	size_t n_elems;
	size_t magic;
	elem_destroy_fn elem_destroy;
} vector;

/* ------------------------------------------------------------------------- */

/**
 * List Implementations
 * ------------------------------------------------------------------------- 
 */

/**
 * Struct: list_elem
 * ----------------------------------
 * The private list_elem implementation
 *
 * field 
 */
typedef struct
{
	void **next;
	void **prev;
} list_elem;

/**
 * Struct: list_implementation
 * ----------------------------------
 * The private list implementation
 *
 * field 
 */
typedef struct
{
	void **head;
	void **tail;
	size_t n_elems;
	size_t magic;
	elem_destroy_fn elem_destroy;
	bool alloc_static;
} list;

/* ------------------------------------------------------------------------- */

#endif /* ADT_PRIVATE_IMPLEMENTATIONS_H */