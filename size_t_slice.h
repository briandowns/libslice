#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SIZE_T_H
#define __SIZE_T_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const size_t x, const size_t y, void *user_data);
typedef void (*foreach_func_t)(const size_t item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const size_t x, const size_t y, void *user_data);

typedef struct size_t_slice size_t_slice_t;

/**
 * size_t_slice_new creates a pointer of type size_t_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
size_t_slice_t*
size_t_slice_new(const uint64_t cap);

/**
 * size_t_slice_free frees the memory used by the given pointer. 
 */
void
size_t_slice_free(size_t_slice_t *s);

/**
 * size_t_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
int
size_t_slice_get(size_t_slice_t *s, uint64_t idx);

/**
 * size_t_slice_len returns the length of the slice.
 */
uint64_t
size_t_slice_len(size_t_slice_t *s);

/**
 * size_t_slice_cap returns the capacity of the slice.
 */
uint64_t
size_t_slice_cap(size_t_slice_t *s);

/**
 * size_t_slice_append attempts to append the data to the given array.
 */
void
size_t_slice_append(size_t_slice_t *s, const size_t val);

/**
 * size_t_slice_reverse the contents of the array.
 */
void
size_t_slice_reverse(size_t_slice_t *s);

/**
 * size_t_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
size_t_slice_compare(const size_t_slice_t *s1, const size_t_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * size_t_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
size_t_slice_copy(const size_t_slice_t *s1, size_t_slice_t *s2, bool overwrite);

/**
 * size_t_slice_contains checks to see if the given value is in the slice.
 */
bool
size_t_slice_contains(const size_t_slice_t *s, size_t val);

/**
 * size_t_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
size_t_slice_delete(size_t_slice_t *s, const uint64_t idx);

/**
 * size_t_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
size_t_slice_replace_by_idx(size_t_slice_t *s, const uint64_t idx, const size_t val);

/**
 * size_t_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
size_t_slice_replace_by_val(size_t_slice_t *s, const size_t old_val, const size_t new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
int
size_t_slice_first(size_t_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
int
size_t_slice_last(size_t_slice_t *s);

/**
 * size_t_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
size_t_slice_foreach(size_t_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * size_t_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
size_t_slice_sort(size_t_slice_t *s, sort_compare_func_t sort_compare);

/**
 * size_t_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
size_t_slice_repeat(size_t_slice_t *s, const size_t val, const uint64_t times);

/**
 * size_t_slice_count counts the occurrences of the given value.
 */
uint64_t
size_t_slice_count(size_t_slice_t *s, const size_t val, compare_func_t compare);

/**
 * size_t_slice_grow grows the slice by the given size.
 */
uint64_t
size_t_slice_grow(size_t_slice_t *s, const uint64_t size);

/**
 * size_t_slice_concat combine the second slice into the first.
 */
uint64_t
size_t_slice_concat(size_t_slice_t *s1, const size_t_slice_t *s2);

#endif /** end __SIZE_T_H */
#ifdef __cplusplus
}
#endif
