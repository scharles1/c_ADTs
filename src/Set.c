/**
 * File: Set.c
 * Author: Seth Charles
 * ----------------------
 */
#include "Set.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/**
 * Function: set_init
 * ------------------------------------------------------
 */
set *
set_init (size_t elem_sz, compare_fn cmp_fn, elem_destroy_fn destory_fn)
{
	assert (cmp_fn != NULL);
	assert (elem_sz > 0);
	set *s;

	s = malloc (sizeof (set));
	assert (s != NULL);

	s->elem_sz = elem_sz;
	s->n_elems = 0;
	s->elem_cmp = cmp_fn;
	s->elem_destroy = elem_destroy_fn;
	s->root = NULL;

	return s;
}

/**
 * Function: set_destroy
 * ------------------------------------------------------
 */
void
set_destroy (set *s)
{

}

/**
 * Function: set_is_empty
 * ------------------------------------------------------
 */
bool
set_is_empty (const set *s)
{

}

/**
 * Function: set_size
 * ------------------------------------------------------
 */
size_t 
set_size (const set *s)
{

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