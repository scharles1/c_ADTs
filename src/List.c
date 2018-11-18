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
#define MAGIC_INIT_VALUE       (0x739caf14a2d9e85f)
#define NEXT_PTR_FROM_PREV(P)  ((void **)(P) - 1)
#define PREV_PTR_FROM_NEXT(P)  ((void **)(P) + 1)

/**
 * Function: list_init_static
 * ------------------------------------------------------
 */
void 
list_init_static (list *l, elem_destroy_fn fn)
{
	assert (l != NULL);

	l->head = (void **)&l->tail;
	l->tail = (void **)&l->head;
	l->n_elems = 0;
	l->elem_destroy = fn;
	l->alloc_static = true;
	l->magic = MAGIC_INIT_VALUE;
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

	l->head = (void **)&l->tail;
	l->tail = (void **)&l->head;
	l->n_elems = 0;
	l->elem_destroy = fn;
	l->alloc_static = false;
	l->magic = MAGIC_INIT_VALUE;

	return l;
}

/**
 * Function: list_destroy
 * ------------------------------------------------------
 */
void
list_destroy (list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	void **cur = l->head, **next;

	if (l->elem_destroy)
	{
		while (*cur != (void *)&l->tail)
		{
			; // TODO: implement this
		}
	}

	if (!l->alloc_static)
	{
		free (l);
	}
}

/**
 * Function: list_size
 * ------------------------------------------------------
 */
size_t list_size (const list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	return l->n_elems;

}

/**
 * Function: list_push_front
 * ------------------------------------------------------
 */
void 
list_push_front (list *l, void *new_node)
{
	assert (l != NULL);
	assert (new_node != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	list_elem *to_insert = new_node;
	
	to_insert->next = l->head;
	*(l->head) = (void *)&(to_insert->next);

	to_insert->prev = (void **)&l->head;
	l->head = (void **)&to_insert->prev;

	++l->n_elems;
}

/**
 * Function: list_push_back
 * ------------------------------------------------------
 */
void 
list_push_back (list *l, void *new_node)
{
	assert (l != NULL);
	assert (new_node != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	list_elem *to_insert = new_node;
	
	to_insert->prev = l->tail;
	*(l->tail) = (void *)&(to_insert->prev);

	to_insert->next = (void **)&l->tail;
	l->tail = (void **)&to_insert->next;

	++l->n_elems;
}

/**
 * Function: list_front
 * ------------------------------------------------------
 */
void *
list_front (const list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	return NULL;
}

/**
 * Function: list_back
 * ------------------------------------------------------
 */
void *
list_back (const list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);

	return NULL;
}

/**
 * Function: list_pop_front
 * ------------------------------------------------------
 */
void 
list_pop_front (list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);
	assert (l->n_elems > 0);

	/* TODO: implement */
}

/**
 * Function: list_pop_back
 * ------------------------------------------------------
 */
void 
list_pop_back (list *l)
{
	assert (l != NULL);
	assert (l->magic == MAGIC_INIT_VALUE);
	assert (l->n_elems > 0);

	/* TODO: implement */
}