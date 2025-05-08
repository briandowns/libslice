#ifdef __cplusplus
extern "C" {
#endif

#ifndef __UINT16_H
#define __UINT16_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const uint16_t x, const uint16_t y, void *user_data);
typedef void (*foreach_func_t)(const uint16_t item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const uint16_t x, const uint16_t y, void *user_data);

typedef struct uint16_slice uint16_slice_t;

/**
 * uint16_slice_new creates a pointer of type uint16_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
uint16_slice_t*
uint16_slice_new(const uint64_t cap);

/**
 * uint16_slice_free frees the memory used by the given pointer. 
 */
void
uint16_slice_free(uint16_slice_t *s);

/**
 * uint16_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
int
uint16_slice_get(uint16_slice_t *s, uint64_t idx);

/**
 * uint16_slice_len returns the length of the slice.
 */
uint64_t
uint16_slice_len(uint16_slice_t *s);

/**
 * uint16_slice_cap returns the capacity of the slice.
 */
uint64_t
uint16_slice_cap(uint16_slice_t *s);

/**
 * uint16_slice_append attempts to append the data to the given array.
 */
void
uint16_slice_append(uint16_slice_t *s, const uint16_t val);

/**
 * uint16_slice_reverse the contents of the array.
 */
void
uint16_slice_reverse(uint16_slice_t *s);

/**
 * uint16_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
uint16_slice_compare(const uint16_slice_t *s1, const uint16_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * uint16_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
uint16_slice_copy(const uint16_slice_t *s1, uint16_slice_t *s2, bool overwrite);

/**
 * uint16_slice_contains checks to see if the given value is in the slice.
 */
bool
uint16_slice_contains(const uint16_slice_t *s, uint16_t val);

/**
 * uint16_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
uint16_slice_delete(uint16_slice_t *s, const uint64_t idx);

/**
 * uint16_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
uint16_slice_replace_by_idx(uint16_slice_t *s, const uint64_t idx, const uint16_t val);

/**
 * uint16_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
uint16_slice_replace_by_val(uint16_slice_t *s, const uint16_t old_val, const uint16_t new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
int
uint16_slice_first(uint16_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
int
uint16_slice_last(uint16_slice_t *s);

/**
 * uint16_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
uint16_slice_foreach(uint16_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * uint16_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
uint16_slice_sort(uint16_slice_t *s, sort_compare_func_t sort_compare);

/**
 * uint16_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
uint16_slice_repeat(uint16_slice_t *s, const uint16_t val, const uint64_t times);

/**
 * uint16_slice_count counts the occurrences of the given value.
 */
uint64_t
uint16_slice_count(uint16_slice_t *s, const uint16_t val, compare_func_t compare);

/**
 * uint16_slice_grow grows the slice by the given size.
 */
uint64_t
uint16_slice_grow(uint16_slice_t *s, const uint64_t size);

/**
 * uint16_slice_concat combine the second slice into the first.
 */
uint64_t
uint16_slice_concat(uint16_slice_t *s1, const uint16_slice_t *s2);

#endif /** end __UINT16_H */
#ifdef __cplusplus
}
#endif
