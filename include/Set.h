/** 
 * File: Set.h
 * ------------------------------------------------------
 * Defines the interface for the set type. This implements the standard
 * ADT set
 */

#ifndef SET_H
#define SET_H

#include "ADT_common.h"
#include "ADT_private_implementations.h"

/**
 * Function: set_init
 * Usage: 
 * ------------------------------------------------------
 * Creates a new empty set.
 */
set *set_init (compare_fn cmp_fn, elem_destroy_fn destory_fn);

/**
 * Function: set_destroy
 * Usage: 
 * ------------------------------------------------------
 */
void set_destroy (set *s);

/**
 * Function: set_is_empty
 * Usage: 
 * ------------------------------------------------------
 */
bool set_is_empty (const set *s);

/**
 * Function: set_size
 * Usage: 
 * ------------------------------------------------------
 */
size_t set_size (const set *s);

/**
 * Function: set_contains
 * Usage: 
 * ------------------------------------------------------
 */
bool set_contains (const set *s, const void *key);

/**
 * Function: set_add
 * Usage: 
 * ------------------------------------------------------
 */
void set_add (set *s, const void *key);

/**
 * Function: set_remove
 * Usage: 
 * ------------------------------------------------------
 */
bool set_remove (set *s, const void *key);

#endif /* SET_H */