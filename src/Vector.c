/**
 * File: vector.c
 * Author: Seth Charles
 * ----------------------
 */
#include "Vector.h"
#include <assert.h>
#include <string.h>

#define DEFAULT_CAPACITY      (16)
#define ELEM_ACCESS(V, INDEX) ((char *)(V->elems) + ((INDEX) * (V->elem_sz)))

/**
 * Struct: vector_implementation
 * ----------------------------------
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
 */
static void
vector_double_capacity (vector *v)
{
	void *larger;
	larger = realloc (v->elems, v->capacity * 2);
	assert (larger != NULL);

	v->elems = larger;
}

/**
 * Function: vector_init
 * ------------------------------------------------------
 */
vector *
vector_init (size_t elem_sz, size_t capacity_hint, elem_destroy_fn fn)
{
	assert (elem_sz > 0);
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
 */
size_t 
vector_size (vector *v)
{
	assert (v != NULL);
	return v->n_elems;
}

/**
 * Function: vector_elem
 * ------------------------------------------------------
 */
void *
vector_elem (vector *v, int index)
{
	assert (v != NULL);
	void *ptr = NULL;

	if (index < v->n_elems)
	{
		ptr = ELEM_ACCESS (v, index);
	}

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
	return;
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

	if (v->n_elems == v->capacity)
	{
		vector_double_capacity (v);
	}

	next_elem = ELEM_ACCESS (v, v->n_elems);
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
	return;
}

/**
 * Function: vector_clear
 * ------------------------------------------------------
 */
void vector_clear (vector *v)
{
	assert (v != NULL);
	size_t i;

	if (v->elem_destroy)
	{
		for (i = 0; i < v->n_elems; i++)
		{
			v->elem_destroy (vector_elem (v, i));
		}
	}

	v->n_elems = 0;
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