#ifdef __cplusplus
extern "C" {
#endif

#ifndef __INT8_H
#define __INT8_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const int8_t x, const int8_t y, void *user_data);
typedef void (*foreach_func_t)(const int8_t item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const int8_t x, const int8_t y, void *user_data);

typedef struct int8_slice int8_slice_t;

/**
 * int8_slice_new creates a pointer of type int8_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
int8_slice_t*
int8_slice_new(const uint64_t cap);

/**
 * int8_slice_free frees the memory used by the given pointer. 
 */
void
int8_slice_free(int8_slice_t *s);

/**
 * int8_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
int
int8_slice_get(int8_slice_t *s, uint64_t idx);

/**
 * int8_slice_len returns the length of the slice.
 */
uint64_t
int8_slice_len(int8_slice_t *s);

/**
 * int8_slice_cap returns the capacity of the slice.
 */
uint64_t
int8_slice_cap(int8_slice_t *s);

/**
 * int8_slice_append attempts to append the data to the given array.
 */
void
int8_slice_append(int8_slice_t *s, const int8_t val);

/**
 * int8_slice_reverse the contents of the array.
 */
void
int8_slice_reverse(int8_slice_t *s);

/**
 * int8_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
int8_slice_compare(const int8_slice_t *s1, const int8_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * int8_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
int8_slice_copy(const int8_slice_t *s1, int8_slice_t *s2, bool overwrite);

/**
 * int8_slice_contains checks to see if the given value is in the slice.
 */
bool
int8_slice_contains(const int8_slice_t *s, int8_t val);

/**
 * int8_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
int8_slice_delete(int8_slice_t *s, const uint64_t idx);

/**
 * int8_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
int8_slice_replace_by_idx(int8_slice_t *s, const uint64_t idx, const int8_t val);

/**
 * int8_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
int8_slice_replace_by_val(int8_slice_t *s, const int8_t old_val, const int8_t new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
int
int8_slice_first(int8_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
int
int8_slice_last(int8_slice_t *s);

/**
 * int8_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
int8_slice_foreach(int8_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * int8_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
int8_slice_sort(int8_slice_t *s, sort_compare_func_t sort_compare);

/**
 * int8_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
int8_slice_repeat(int8_slice_t *s, const int8_t val, const uint64_t times);

/**
 * int8_slice_count counts the occurrences of the given value.
 */
uint64_t
int8_slice_count(int8_slice_t *s, const int8_t val, compare_func_t compare);

/**
 * int8_slice_grow grows the slice by the given size.
 */
uint64_t
int8_slice_grow(int8_slice_t *s, const uint64_t size);

/**
 * int8_slice_concat combine the second slice into the first.
 */
uint64_t
int8_slice_concat(int8_slice_t *s1, const int8_slice_t *s2);

#endif /** end __INT8_H */
#ifdef __cplusplus
}
#endif
