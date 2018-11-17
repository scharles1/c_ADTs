/**
 * File: vector.c
 * Author: Seth Charles
 * ----------------------
 */
#include "Vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <search.h>

#define DEFAULT_CAPACITY       (16UL)
#define GET_PTR_ELEM(V, INDEX) ((char *)(V->elems) + ((INDEX) * (V->elem_sz)))

/**
 * Struct: vector_implementation
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
struct vector_implementation
{
	void *elems;
	size_t capacity;
	size_t elem_sz;
	size_t n_elems;
	elem_destroy_fn elem_destroy;
};

/**
 * Function: vector_double_capacity
 * ------------------------------------------------------
 * Module function to handle dynamic resize of a vector's capacity
 * 
 * param v - a pointer to the vector to resize
 */
static void
vector_double_capacity (vector *v)
{
	void *larger;
	size_t new_capacity =  v->capacity * 2;

	larger = realloc (v->elems, new_capacity * v->elem_sz);
	assert (larger != NULL);

	v->capacity = new_capacity;
	v->elems = larger;
}

/**
 * Function: vector_init
 * ------------------------------------------------------
 * Public function to perform vector initialization
 *
 * param elem_sz       - the size of elements in bytes that are stored
 * param capacity_hint - a capacity suggestion for initialization
 * param fn            - the cleanup function to call when an element is destroyed
 *
 * returns - a pointer to the vector object
 */
vector *
vector_init (size_t elem_sz, size_t capacity_hint, elem_destroy_fn fn)
{
	vector *v;

	/* allocate space for the vector object */
	v = (vector *)malloc (sizeof (vector));
	assert (v != NULL);

	/* allocate space for the elements in the vector */
	v->capacity = (capacity_hint == 0) ? DEFAULT_CAPACITY : capacity_hint;
	v->elems = malloc (v->capacity * elem_sz);
	assert (v->elems != NULL);
	
	v->elem_sz = elem_sz;
	v->n_elems = 0;
	v->elem_destroy = fn;

	return v;
}

/**
 * Function: vector_destroy
 * ------------------------------------------------------
 * Destroys the vector and deallocates all the memory used for the vector. Also
 * calls the provided element destroy function on individual elements.
 *
 * param v - the vector to destroy
 */
void 
vector_destroy (vector *v)
{
	assert (v != NULL);

	vector_clear (v);
	free (v->elems);
	free (v);
}

/**
 * Function: vector_size
 * ------------------------------------------------------
 * Returns the current number of elements stored in the vector.
 *
 * param v - initialized vector
 *
 * returns - number of elements stored in the vector
 */
size_t 
vector_size (const vector *v)
{
	assert (v != NULL);
	return v->n_elems;
}

/**
 * Function: vector_access
 * ------------------------------------------------------
 * Provides a pointer to the vector element corresponding the provided index
 *
 * param v     - initialized vector
 * param index - the index to access
 *
 * returns     - a pointer the corresponding index in the vector
 */
void *
vector_access (vector *v, int index)
{
	assert (v != NULL);
	void *ptr;

	ptr = GET_PTR_ELEM (v, index);

	return ptr;
}

/**
 * Function: vector_insert
 * ------------------------------------------------------
 */
void 
vector_insert (vector *v, const void *elem, int index)
{
	assert (v != NULL);
	assert (elem != NULL);
	assert (index <= v->n_elems);

	void *insert_at, *next;

	if (v->n_elems == v->capacity)
	{
		vector_double_capacity (v);
	}

	insert_at = GET_PTR_ELEM (v, index);
	next = GET_PTR_ELEM (v, index + 1);

	memmove (next, insert_at, (v->n_elems - index) * (v->elem_sz));
	memcpy (insert_at, elem, v->elem_sz);

	++v->n_elems;
}

/**
 * Function: vector_remove
 * Usage: vector_remove (v, 0)
 * ------------------------------------------------------
 */
void 
vector_remove (vector *v, int index)
{
	assert (v != NULL);
	assert (index < v->n_elems);

	void *remove_at, *next;

	remove_at = GET_PTR_ELEM (v, index);
	next = GET_PTR_ELEM (v, index + 1);

	if (v->elem_destroy)
	{
		v->elem_destroy (remove_at);
	}

	--v->n_elems;
	memmove (remove_at, next, (v->n_elems - index) * (v->elem_sz));
}

/**
 * Function: vector_append
 * ------------------------------------------------------
 */
void 
vector_append (vector *v, const void *elem)
{
	assert (v != NULL);
	assert (elem != NULL);
	void *next_elem;

	if (v->capacity <= v->n_elems)
	{
		vector_double_capacity (v);
	}

	next_elem = GET_PTR_ELEM (v, v->n_elems);
	memcpy (next_elem, elem, v->elem_sz);
	++v->n_elems;
}

/**
 * Function: vector_replace
 * ------------------------------------------------------
 */
void 
vector_replace (vector *v, const void *elem, int index)
{
	assert (v != NULL);
	assert (elem != NULL);
	assert (index < v->n_elems);
	void *to_replace;

	to_replace = GET_PTR_ELEM (v, index);
	if (v->elem_destroy)
	{
		v->elem_destroy (to_replace);
	}

	memcpy (to_replace, elem, v->elem_sz);
}

/**
 * Function: vector_clear
 * ------------------------------------------------------
 */
void 
vector_clear (vector *v)
{
	assert (v != NULL);
	size_t i;

	if (v->elem_destroy)
	{
		for (i = 0; i < v->n_elems; i++)
		{
			v->elem_destroy (vector_access (v, i));
		}
	}

	v->n_elems = 0;
}

/**
 * Function: vector_search
 * ------------------------------------------------------
 */
void *
vector_search (const vector *v, const void *key, compare_fn fn, bool sorted)
{
	assert (v != NULL);
	assert (key != NULL);
	void *ptr;

	size_t n_elems = v->n_elems;

	if (sorted) /* binary search */
	{
		ptr = bsearch (key, v->elems, v->n_elems, v->elem_sz, fn);
	}
	else /* linear search */
	{
		ptr = lfind (key, v->elems, &n_elems, v->elem_sz, fn);
	}

	return ptr;
}

/**
 * Function: vector_sort
 * ------------------------------------------------------
 */
void 
vector_sort (vector *v, compare_fn fn)
{
	qsort (v->elems, v->n_elems, v->elem_sz, fn);
}