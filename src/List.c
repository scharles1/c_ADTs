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
	size_t magic;
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

	l->head = l->tail = NULL;
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
	to_insert->prev = NULL;
	l->head = to_insert;

	if (l->tail == NULL)
	{
		l->tail = to_insert;
	}

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
	to_insert->next = NULL;
	l->tail = to_insert;

	if (l->head == NULL)
	{
		l->head = to_insert;
	}

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

	return l->head;
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

	return l->tail;
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

	list_elem *old_head, *new_head;

	old_head = l->head;
	new_head = old_head->next;

	if (l->n_elems == 1)
	{
		l->head = l->tail = NULL;
	}
	else
	{
		l->head = new_head;
		new_head->prev = NULL;
	}

	if (l->elem_destroy)
	{
		l->elem_destroy (old_head);
	}

	--l->n_elems;
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

	list_elem *old_tail, *new_tail;

	old_tail = l->tail;
	new_tail = old_tail->prev;

	if (l->n_elems == 1)
	{
		l->head = l->tail = NULL;
	}
	else
	{
		l->tail = new_tail;
		new_tail->next = NULL;
	}

	if (l->elem_destroy)
	{
		l->elem_destroy (old_tail);
	}

	--l->n_elems;
}