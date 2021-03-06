/**
 * File: Vector.c
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
#define MAGIC_INIT_VALUE       (0x739caf14a2d9e85f)

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
	v->magic = MAGIC_INIT_VALUE;

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
	assert (v->magic == MAGIC_INIT_VALUE);

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
	assert (v->magic == MAGIC_INIT_VALUE);

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
	assert (v->magic == MAGIC_INIT_VALUE);

	void *ptr;

	ptr = GET_PTR_ELEM (v, index);

	return ptr;
}

/**
 * Function: vector_insert
 * ------------------------------------------------------
 * Inserts an element at the provided index. Shifts all later elements back by
 * one element space to create space for the new element.
 *
 * param v     - initialized vector
 * param elem  - a pointer to the new element data to insert by copy
 * param index - the index to insert at
 */
void 
vector_insert (vector *v, const void *elem, int index)
{
	assert (v != NULL);
	assert (elem != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Removes an element at the provided index. Shifts all later elements up by
 * one element space to fill the whole. The cleanup function is called on 
 * the removed element.
 *
 * param v     - initialized vector
 * param index - the index to remove at
 */
void 
vector_remove (vector *v, int index)
{
	assert (v != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Appends an element to the end of the vector.
 *
 * param v    - initialized vector
 * param elem - a pointer to the new element data to append by copy
 */
void 
vector_append (vector *v, const void *elem)
{
	assert (v != NULL);
	assert (elem != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Replaces an element at the provided index. The data at elem is copied into 
 * the vector at the index and the old element is destroyed.
 *
 * param v     - initialized vector
 * param elem  - a pointer to the new element data to replace by copy
 * param index - the index to replace
 */
void 
vector_replace (vector *v, const void *elem, int index)
{
	assert (v != NULL);
	assert (elem != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Internally clears the entire vector and calls the provided destroy fuction
 * on each element. After calling this the vector has 0 elements. It's previous
 * storage capacity is not modified.
 *
 * param v - initialized vector
 */
void 
vector_clear (vector *v)
{
	assert (v != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Searches the vector for an element matching the key utilizing the provided
 * compare function. The sorted flag controls whether to use a binary search on
 * an already sorted vector verses a linear search on an unsorted vector.
 *
 * param v      - initialized vector
 * param key    - a pointer to the data to find in the vector
 * param fn     - a compare function for searching
 * param sorted - a flag provided to signal whether the vector is sorted
 *
 * returns - a pointer to the matching vector element or NULL if it doesn't 
 *           contain the key
 */
void *
vector_search (const vector *v, const void *key, compare_fn fn, bool sorted)
{
	assert (v != NULL);
	assert (key != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);
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
 * Sorts the provided vector according to the provided compare function. Uses
 * the quicksort algorithm.
 *
 * param v  - initialized vector
 * param fn - the provided compare function for sorting
 */
void 
vector_sort (vector *v, compare_fn fn)
{
	assert (v != NULL);
	assert (v->magic == MAGIC_INIT_VALUE);

	qsort (v->elems, v->n_elems, v->elem_sz, fn);
}