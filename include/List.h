/** 
 * File: List.h
 * ------------------------------------------------------
 * Defines the interface for the list type. This implements the standard
 * ADT doubly linked list type.
 */

#ifndef LIST_H
#define LIST_H

#include "ADT_common.h"

/**
 * Type: list
 * ------------------------------------------------------
 * The intention with this type is to hide the internals of the list struct
 * by defining the list_implementation struct in the LIST.c file. This 
 * requires clients to use the prescribed API
 */
typedef struct list_implementation list;

/**
 * Type: list_elem
 * ------------------------------------------------------
 * The intention with this type is to hide the internals of the list_elem
 * struct by defining the list_elem_implementation struct in the LIST.c file. 
 * This requires clients to use the prescribed API
 */
typedef struct list_elem_implementation list_elem;

/**
 * Function: list_init_static
 * Usage: list l;
 *        list_init (&l);
 * ------------------------------------------------------
 * Creates a new empty list. The space for the list object is allocated by the
 * caller.
 */
void list_init_static (list *l, elem_destroy_fn fn);

/**
 * Function: list_init
 * Usage: list *v = list_init (void)
 * ------------------------------------------------------
 * Creates a new empty list and returns it to the caller
 */
list *list_init (elem_destroy_fn fn);

/**
 * Function: list_destroy
 * Usage: list_destroy (l)
 * ------------------------------------------------------
 * Destroys and frees all memory associated with list
 *
 * Asserts: null pointer
 * Assumes: valid initialized vector pointer
 */
void list_destroy (list *l);

void list_push_front (list *l, void *new_node);

void list_push_back (list *l, void *new_node);

void *list_front (list *l);

void *list_back (list *l);

void list_pop_front (list *l);

void list_pop_back (list *l);

#endif /* LIST_H */