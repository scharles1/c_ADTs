/**
 * File: Set.c
 * Author: Seth Charles
 * ----------------------
 */
#include "Set.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define MAGIC_INIT_VALUE (0x739caf14a2d9e85f)

/**
 * Function: set_init
 * ------------------------------------------------------
 */
set *
set_init (size_t elem_sz, compare_fn cmp_fn, elem_destroy_fn destroy_fn)
{
	assert (cmp_fn != NULL);
	assert (elem_sz > 0);
	set *s;

	s = malloc (sizeof (set));
	assert (s != NULL);

	memset (s, 0, sizeof (set));
	s->elem_sz = elem_sz;
	s->elem_cmp = cmp_fn;
	s->elem_destroy = destroy_fn;
	s->magic = MAGIC_INIT_VALUE;

	return s;
}

/**
 * Function: set_destroy
 * ------------------------------------------------------
 */
void
set_destroy (set *s)
{
	assert (s != NULL);
	assert (s->magic = MAGIC_INIT_VALUE);

	if (s->elem_destroy)
	{
		/* TODO: need to traverse tree and free all the leaves */
	}

	free (s);
}

/**
 * Function: set_is_empty
 * ------------------------------------------------------
 */
bool
set_is_empty (const set *s)
{
	assert (s != NULL);
	assert (s->magic = MAGIC_INIT_VALUE);

	return (s->n_elems == 0);
}

/**
 * Function: set_size
 * ------------------------------------------------------
 */
size_t 
set_size (const set *s)
{
	assert (s != NULL);
	assert (s->magic = MAGIC_INIT_VALUE);

	return s->n_elems;
}

/**
 * Function: set_contains
 * ------------------------------------------------------
 */
bool
set_contains (const set *s, const void *key)
{

}

/**
 * Function: set_add
 * ------------------------------------------------------
 */
void 
set_add (set *s, const void *key)
{

}

/**
 * Function: set_remove
 * ------------------------------------------------------
 */
bool 
set_remove (set *s, const void *key)
{

}