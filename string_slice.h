#ifdef __cplusplus
extern "C" {
#endif

#ifndef __STRING_H
#define __STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef bool (*compare_func_t)(const char *x, const char *y, void *user_data);
typedef void (*foreach_func_t)(const char *item, void *user_data);
typedef int  (*sort_compare_func_t)(const void *x, const void *y);
typedef bool (*val_equal_func_t)(const char *x, const char *y, void *user_data);

typedef struct {
    char **items;
    uint64_t len;
    uint64_t cap;
} string_slice_t;

/**
 * string_slice_new creates a pointer of type string_slice_t, sets
 * default values, and returns the pointer to the allocated memory. The user
 * is responsible for freeing this memory.
 */
string_slice_t*
string_slice_new(const uint64_t cap);

/**
 * string_slice_free frees the memory used by the given pointer. 
 */
void
string_slice_free(string_slice_t *s);

/**
 * string_slice_get attempts to retrieve the value at the given index. If
 * the index is out of range, 0 is returned indicating an error.
 */
char*
string_slice_get(string_slice_t *s, uint64_t idx);

/**
 * string_slice_append attempts to append the data to the given array.
 */
void
string_slice_append(string_slice_t *s, const char *val);

/**
 * string_slice_reverse the contents of the array.
 */
void
string_slice_reverse(string_slice_t *s);

/**
 * string_slice_compare takes 2 slices, compares them element by element
 * and returns true if they are the same and false if they are not.
 */
bool
string_slice_compare(const string_slice_t *s1, const string_slice_t *s2, compare_func_t compare, void *user_data);

/**
 * string_slice_copy takes 2 slices. The first is copied into the second
 * with the number of elements copied being returned. The code assumes that 
 * slice 2 has been created large enough to hold the contents of slice 1. If
 * the overwrite option has been selected, the code will make sure there is 
 * enough space in slice 2 and overwrite its contents.
 */
uint64_t
string_slice_copy(const string_slice_t *s1, string_slice_t *s2, bool overwrite);

/**
 * string_slice_contains checks to see if the given value is in the slice.
 */
bool
string_slice_contains(const string_slice_t *s, char *val);

/**
 * string_slice_delete removes the item at the given index and returns the
 * new length.
 */
int
string_slice_delete(string_slice_t *s, const uint64_t idx);

/**
 * string_slice_replace_by_idx replaces the value at the given index with the new
 * value.
 */
int
string_slice_replace_by_idx(string_slice_t *s, const uint64_t idx, const char *val);

/**
 * string_slice_replace_by_val replaces occurrences of the value with the
 * new value, the number of times given. 
 */
int
string_slice_replace_by_val(string_slice_t *s, const char *old_val, const char *new_val, uint64_t times, compare_func_t compare);

/**
 * uint_slice returns the first element of the slice.
 */
char*
string_slice_first(string_slice_t *s);

/**
 * uint_slice returns the last element of the slice.
 */
char*
string_slice_last(string_slice_t *s);

/**
 * string_slice_foreach iterates through the slice and runs the user provided
 * function on each item. Additional user data can be provided using the
 * user_data argument.
 */
int
string_slice_foreach(string_slice_t *s, foreach_func_t ift, void *user_data);

/**
 * string_slice_sort uses that Quick Sort algorithm to sort the contents
 * of the slice.
 */
void
string_slice_sort(string_slice_t *s, sort_compare_func_t sort_compare);

/**
 * string_slice_repeat takes a value and repeats that value in the slice
 * for the number of times given and returns the new length of the slice.
 */
uint64_t
string_slice_repeat(string_slice_t *s, const char *val, const uint64_t times);

/**
 * string_slice_count counts the occurrences of the given value.
 */
uint64_t
string_slice_count(string_slice_t *s, const char *val, compare_func_t compare);

/**
 * string_slice_grow grows the slice by the given size.
 */
uint64_t
string_slice_grow(string_slice_t *s, const uint64_t size);

/**
 * string_slice_concat combine the second slice into the first.
 */
uint64_t
string_slice_concat(string_slice_t *s1, const string_slice_t *s2);

#endif /** end __STRING_H */
#ifdef __cplusplus
}
#endif
