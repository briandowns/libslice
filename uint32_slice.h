#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UINT32_H
#define __UINT32_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const uint32_t x, const uint32_t y, void *user_data);
typedef void (*foreach_func_t)(const uint32_t item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const uint32_t x, const uint32_t y, void *user_data);

typedef struct uint32_slice uint32_slice_t;

/**
 * uint32_slice_new creates a pointer of type uint32_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
uint32_slice_t*
uint32_slice_new(const uint64_t cap);

/**
 * uint32_slice_free frees the memory used by the given pointer. 
 */
void
uint32_slice_free(uint32_slice_t *s);

/**
 * uint32_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
int
uint32_slice_get(uint32_slice_t *s, uint64_t idx);

/**
 * uint32_slice_len returns the length of the slice.
 */
uint64_t
uint32_slice_len(uint32_slice_t *s);

/**
 * uint32_slice_cap returns the capacity of the slice.
 */
uint64_t
uint32_slice_cap(uint32_slice_t *s);

/**
 * uint32_slice_append attempts to append the data to the given array.
 */
void
uint32_slice_append(uint32_slice_t *s, const uint32_t val);

/**
 * uint32_slice_reverse the contents of the array.
 */
void
uint32_slice_reverse(uint32_slice_t *s);

/**
 * uint32_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
uint32_slice_compare(const uint32_slice_t *s1, const uint32_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * uint32_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
uint32_slice_copy(const uint32_slice_t *s1, uint32_slice_t *s2, bool overwrite);

/**
 * uint32_slice_contains checks to see if the given value is in the slice.
 */
bool
uint32_slice_contains(const uint32_slice_t *s, uint32_t val);

/**
 * uint32_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
uint32_slice_delete(uint32_slice_t *s, const uint64_t idx);

/**
 * uint32_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
uint32_slice_replace_by_idx(uint32_slice_t *s, const uint64_t idx, const uint32_t val);

/**
 * uint32_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
uint32_slice_replace_by_val(uint32_slice_t *s, const uint32_t old_val, const uint32_t new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
int
uint32_slice_first(uint32_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
int
uint32_slice_last(uint32_slice_t *s);

/**
 * uint32_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
uint32_slice_foreach(uint32_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * uint32_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
uint32_slice_sort(uint32_slice_t *s, sort_compare_func_t sort_compare);

/**
 * uint32_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
uint32_slice_repeat(uint32_slice_t *s, const uint32_t val, const uint64_t times);

/**
 * uint32_slice_count counts the occurrences of the given value.
 */
uint64_t
uint32_slice_count(uint32_slice_t *s, const uint32_t val, compare_func_t compare);

/**
 * uint32_slice_grow grows the slice by the given size.
 */
uint64_t
uint32_slice_grow(uint32_slice_t *s, const uint64_t size);

/**
 * uint32_slice_concat combine the second slice into the first.
 */
uint64_t
uint32_slice_concat(uint32_slice_t *s1, const uint32_slice_t *s2);

#endif /** end __UINT32_H */
#ifdef __cplusplus
}
#endif
