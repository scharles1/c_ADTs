/** 
 * File: ADT_common.h
 * ------------------------------------------------------
 * Shared definitions used between the ADT library implementations
 */

#ifndef ADT_COMMON_H
#define ADT_COMMON_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Type: elem_destroy_fn
 * ------------------------------------------------------
 * The client can create ADTs that hold complex objects. When adding an 
 * object to a containter, the ownership of that object is transferred to the
 * container module and the necessary cleanup required when destroyed is done 
 * on each object via this function provided by the client.
 */
typedef void (*elem_destroy_fn) (void *addr);

/**
 * Type: compare_fn
 * ------------------------------------------------------
 * Typedef for compare function used for sorting and searching.
 */
typedef int (*compare_fn) (const void *elem1, const void *elem2);

#endif /* ADT_COMMON_H */