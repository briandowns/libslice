#ifndef __SLICE_H
#define __SLICE_H

#include <stdint.h>

typedef struct slice slice_t;

typedef enum {
    S_UINT, S_UINT8, S_UINT16, S_UINT32, S_UINT64,
    S_INT, S_INT8, S_INT16, S_INT32, S_INT64,
    S_SIZET
} slice_type_t;

/**
 * slice_new creates a pointer of type slice_t, sets default values, and
 * returns the pointer to the allocated memory. The user is responsible
 * for freeing this memory.
 */
slice_t*
slice_new(const slice_type_t type, const uint64_t cap);

/**
 * slice_free frees the memory used by the given pointer. 
 */
void
slice_free(slice_t *s);

// #define FOO(A) ({int retval; retval = do_something(A); retval;})

/**
 * slice_append attempts to append the data to the given array.
 */
#define slice_get(s, idx) ({ \
    void *ret = NULL; \
    slice_t *sl = (slice_t*)s; \
    ret = __slice_get(sl, idx); \
    switch (sl->type) { case S_UINT: *(unsigned int*)ret; } \
})

/**
 * slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
void*
__slice_get(slice_t *s, uint64_t idx);

/**
 * slice_len returns the length of the slice.
 */
uint64_t
slice_len(slice_t *s);

/**
 * slice_cap returns the capacity of the slice.
 */
uint64_t
slice_cap(slice_t *s);

/**
 * slice_append attempts to append the data to the given array.
 */
#define slice_append(s, val) \
    const void *v = &val; \
    slice_t *sl = (slice_t*)s; \
    __slice_append(sl, v);

/**
 * slice_append attempts to append the data to the given array.
 */
void
__slice_append(slice_t *s, const void *val);

#endif /** end __SLICE_H */
