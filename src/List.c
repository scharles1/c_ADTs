/**
 * File: List.c
 * Author: Seth Charles
 * ----------------------
 */
#include "List.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define GET_PTR_ELEM(V, INDEX) ((char *)(V->elems) + ((INDEX) * (V->elem_sz)))

/**
 * Struct: list_implementation
 * ----------------------------------
 * The private list implementation
 *
 * field 
 */
struct list_implementation
{
	list_elem *head;
	list_elem *tail;
	size_t n_elems;
	elem_destroy_fn elem_destroy;
	bool alloc_static;
};

/**
 * Struct: list_elem_implementation
 * ----------------------------------
 * The private list_elem implementation
 *
 * field 
 */
struct list_elem_implementation
{
	list_elem *next;
	list_elem *prev;
};

/**
 * Function: list_init_static
 * ------------------------------------------------------
 */
void 
list_init_static (list *l, elem_destroy_fn fn)
{
	assert (l != NULL);

	l->head = l->tail = NULL;
	l->n_elems = 0;
	l->elem_destroy = fn;
	l->alloc_static = true;
}

/**
 * Function: list_init
 * ------------------------------------------------------
 */
list *
list_init (elem_destroy_fn fn)
{
	list *l = malloc (sizeof (list));
	assert (l != NULL);

	l->head = l->tail = NULL;
	l->n_elems = 0;
	l->elem_destroy = fn;
	l->alloc_static = false;

	return l;
}

/**
 * Function: list_destroy
 * Usage: list_destroy (l)
 * ------------------------------------------------------
 * Destroys and frees all memory associated with list
 *
 * Asserts: null pointer
 * Assumes: valid initialized vector pointer
 */
void
list_destroy (list *l)
{
	assert (l != NULL);

	list_elem *l_elem, *l_elem_next;

	if (l->elem_destroy)
	{
		l_elem = l->head;
		while (l_elem)
		{
			l_elem_next = l_elem->next;
			l->elem_destroy (l_elem);
			l_elem = l_elem_next;
		}
	}

	if (!l->alloc_static)
	{
		free (l);
	}
}