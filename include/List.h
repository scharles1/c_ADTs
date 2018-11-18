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
 * The use for this list API requires the client to embed the list_elem object
 * as the first field of a struct that will be the nodes of the list.
 *
 * For example, to make a list storing simple unsigned integers:
 * 
 * typedef struct
 * {
 *  	list_elem le;
 *  	unsigned data;
 * } my_node_t;
 * 
 * list *l = list_init (NULL);
 * my_node_t to_insert;
 * to_insert->data = 0xdeadbeef;
 * list_push_front (l, &to_insert);
 */

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

/**
 * Function: list_size
 * Usage: size_t size = list_size (l)
 * ------------------------------------------------------
 * Returns the number of elements in the list.
 *
 */
size_t list_size (const list *l);

/**
 * Function: list_push_front
 * Usage: list_push_front (l, &new_node)
 * ------------------------------------------------------
 * Pushes a new node onto the front of the list
 */
void list_push_front (list *l, void *new_node);

/**
 * Function: list_push_back
 * Usage: list_push_back (l, &new_node)
 * ------------------------------------------------------
 */
void list_push_back (list *l, void *new_node);

/**
 * Function: list_front
 * Usage: my_node_t *front = list_front (l)
 * ------------------------------------------------------
 */
void *list_front (const list *l);

/**
 * Function: list_back
 * Usage: my_node_t *back = list_back (l)
 * ------------------------------------------------------
 */
void *list_back (const list *l);

/**
 * Function: list_pop_front
 * Usage: list_pop_front (l)
 * ------------------------------------------------------
 */
void list_pop_front (list *l);

/**
 * Function: list_pop_back
 * Usage: list_pop_back (l)
 * ------------------------------------------------------
 */
void list_pop_back (list *l);

#endif /* LIST_H */