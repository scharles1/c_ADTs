/**
 * File: vector.c
 * Author: Seth Charles
 * ----------------------
 */
#include "Vector.h"

#define DEFAULT_CAPACITY 16

/**
 * Struct: vector_implementation
 * ----------------------------------
 */
struct vector_implementation
{
	void *elems;
	size_t capacity;
	size_t elemsz;
	size_t n_elems;
	elem_destroy_fn elem_destroy;
};

/**
 * Function: vector_init
 * ------------------------------------------------------
 */
vector *
vector_init (size_t elem_sz, size_t capacity_hint, elem_destroy_fn fn)
{
	size_t capacity;
	vector *v;

	return v;
}

/**
 * Function: vector_destroy
 * ------------------------------------------------------
 */
void 
vector_destroy (vector *v)
{
	return;
}

/**
 * Function: vector_size
 * ------------------------------------------------------
 */
size_t 
vector_size (vector *v)
{
	return 0;
}

/**
 * Function: vector_elem
 * ------------------------------------------------------
 */
void *
vector_elem (vector *v, int index)
{
	return NULL;
}

/**
 * Function: vector_insert
 * ------------------------------------------------------
 */
void 
vector_insert (vector *v, const void *elem, int index)
{
	return;
}

/**
 * Function: vector_append
 * ------------------------------------------------------
 */
void 
vector_append (vector *v, const void *elem)
{
	return;
}

/**
 * Function: vector_replace
 * ------------------------------------------------------
 */
void 
vector_replace (vector *v, const void *elem, int index)
{
	return;
}

/**
 * Function: vector_search
 * ------------------------------------------------------
 */
int 
vector_search (const vector *v, const void *key, compare_fn fn, bool sorted)
{
	return 0;
}

/**
 * Function: vector_sort
 * ------------------------------------------------------
 */
void 
vector_sort (vector *v, compare_fn fn)
{
	return;
}