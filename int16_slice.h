#ifdef __cplusplus
extern "C" {
#endif

#ifndef __INT16_H
#define __INT16_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const int16_t x, const int16_t y, void *user_data);
typedef void (*foreach_func_t)(const int16_t item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const int16_t x, const int16_t y, void *user_data);

typedef struct int16_slice int16_slice_t;

/**
 * int16_slice_new creates a pointer of type int16_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
int16_slice_t*
int16_slice_new(const uint64_t cap);

/**
 * int16_slice_free frees the memory used by the given pointer. 
 */
void
int16_slice_free(int16_slice_t *s);

/**
 * int16_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
int
int16_slice_get(int16_slice_t *s, uint64_t idx);

/**
 * int16_slice_len returns the length of the slice.
 */
uint64_t
int16_slice_len(int16_slice_t *s);

/**
 * int16_slice_cap returns the capacity of the slice.
 */
uint64_t
int16_slice_cap(int16_slice_t *s);

/**
 * int16_slice_append attempts to append the data to the given array.
 */
void
int16_slice_append(int16_slice_t *s, const int16_t val);

/**
 * int16_slice_reverse the contents of the array.
 */
void
int16_slice_reverse(int16_slice_t *s);

/**
 * int16_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
int16_slice_compare(const int16_slice_t *s1, const int16_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * int16_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
int16_slice_copy(const int16_slice_t *s1, int16_slice_t *s2, bool overwrite);

/**
 * int16_slice_contains checks to see if the given value is in the slice.
 */
bool
int16_slice_contains(const int16_slice_t *s, int16_t val);

/**
 * int16_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
int16_slice_delete(int16_slice_t *s, const uint64_t idx);

/**
 * int16_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
int16_slice_replace_by_idx(int16_slice_t *s, const uint64_t idx, const int16_t val);

/**
 * int16_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
int16_slice_replace_by_val(int16_slice_t *s, const int16_t old_val, const int16_t new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
int
int16_slice_first(int16_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
int
int16_slice_last(int16_slice_t *s);

/**
 * int16_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
int16_slice_foreach(int16_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * int16_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
int16_slice_sort(int16_slice_t *s, sort_compare_func_t sort_compare);

/**
 * int16_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
int16_slice_repeat(int16_slice_t *s, const int16_t val, const uint64_t times);

/**
 * int16_slice_count counts the occurrences of the given value.
 */
uint64_t
int16_slice_count(int16_slice_t *s, const int16_t val, compare_func_t compare);

/**
 * int16_slice_grow grows the slice by the given size.
 */
uint64_t
int16_slice_grow(int16_slice_t *s, const uint64_t size);

/**
 * int16_slice_concat combine the second slice into the first.
 */
uint64_t
int16_slice_concat(int16_slice_t *s1, const int16_slice_t *s2);

#endif /** end __INT16_H */
#ifdef __cplusplus
}
#endif
