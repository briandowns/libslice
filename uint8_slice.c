#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "uint8_slice.h"

struct uint8_slice {
    uint8_t *items;
    uint64_t len;
    uint64_t cap;
};

uint8_slice_t*
uint8_slice_new(const uint64_t cap)
{
    uint8_slice_t *s = calloc(1, sizeof(uint8_slice_t));
    s->items = calloc(1, sizeof(uint8_t) * cap);
    s->len = 0;
    s->cap = cap;

    return s;
}

void
uint8_slice_free(uint8_slice_t *s) {
	if (s != NULL && s->items != NULL) {
        free(s->items);
        free(s);
	} 
}

int
uint8_slice_get(uint8_slice_t *s, uint64_t idx)
{
    if (idx >= 0 && idx < s->len) {
        return s->items[idx];
    }

    return 0;
}

uint64_t
uint8_slice_len(uint8_slice_t *s)
{
	if (s == NULL) {
		return 0;
	}

	struct uint8_slice *is = (struct uint8_slice*)s;
	return is->len;
}

uint64_t
uint8_slice_cap(uint8_slice_t *s)
{
	if (s == NULL) {
		return 0;
	}

	struct uint8_slice *is = (struct uint8_slice*)s;
	return is->cap;	
}

void
uint8_slice_append(uint8_slice_t *s, const uint8_t val)
{
    if (s->len == s->cap) {
        s->cap *= 2;
        s->items = realloc(s->items, sizeof(uint8_t) * s->cap);
    }
    s->items[s->len++] = val;
}

void
uint8_slice_reverse(uint8_slice_t *s) {
	if (s->len < 2) {
		return;
	}

    uint64_t i = s->len - 1;
    uint64_t j = 0;

    while(i > j) {
        int temp = s->items[i];
        s->items[i] = s->items[j];
        s->items[j] = temp;
        i--;
        j++;
    }
}

bool
uint8_slice_compare(const uint8_slice_t *s1, const uint8_slice_t *s2, compare_func_t compare, void *user_data)
{
	if (s1->len != s2->len) {
		return false;
	}

	for (uint64_t i = 0; i < s1->len; i++) {
		if (!compare(s1->items[i], s2->items[i], user_data)) {
			return false;
		}
	}

	return true;
}

uint64_t
uint8_slice_copy(const uint8_slice_t *s1, uint8_slice_t *s2, bool overwrite)
{
	if (s2->len == 0) {
		return 0;
	}

	if (overwrite) {
		if (s1->len != s2->len) {
			s2->cap = s1->cap;
			s2->items = realloc(s2->items, sizeof(uint8_t) * s1->cap);
		}
	}

	for (uint64_t i = 0; i < s1->len; i++) {
		s2->items[i] = s1->items[i];
		s2->len++;
	}

	return s2->len;
}

bool
uint8_slice_contains(const uint8_slice_t *s, uint8_t val)
{
	if (s->len == 0) {
		return false;
	}

	for (uint64_t i = 0; i < s->len; i++) {
		if (s->items[i] == val) {
			return true;
		}
	}

	return false;
}

int
uint8_slice_delete(uint8_slice_t *s, const uint64_t idx)
{
	if (s->len == 0 || idx > s->len) {
		return -1;
	}

	for (uint64_t i = idx; i < s->len; i++) {
		s->items[i] = s->items[i + 1];
	}
	s->len--;

	return s->len;
}

int
uint8_slice_replace_by_idx(uint8_slice_t *s, const uint64_t idx, const uint8_t val)
{
	if (s->len == 0 || idx > s->len) {
		return -1;
	}
	s->items[idx] = val;

	return 0;
}

int
uint8_slice_replace_by_val(uint8_slice_t *s, const uint8_t old_val, const uint8_t new_val, uint64_t times, compare_func_t compare)
{
	if (s->len == 0) {
		return -1;
	}

	for (uint64_t i = 0; i < s->len && times != 0; i++) {
		if (compare(s->items[i], old_val, NULL)) {
			s->items[i] = new_val;
			times--;
		}
	}

	return 0;
}

int
uint8_slice_first(uint8_slice_t *s)
{
	return uint8_slice_get(s, 0);
}

int
uint8_slice_last(uint8_slice_t *s)
{
	return uint8_slice_get(s, s->len-1);
}

int
uint8_slice_foreach(uint8_slice_t *s, foreach_func_t ift, void *user_data)
{
	if (s->len == 0) {
		return 0;
	}
	
	for (uint64_t i = 0; i < s->len; i++) {
		ift(s->items[i], user_data);
	}

	return 0;
}

/**
 * qsort_compare is a simple implementation of the function required to be
 * passed to qsort.
 */
static int
qsort_compare(const void *x, const void *y) {
	return (*(int*)x - *(int*)y);
}

void
uint8_slice_sort(uint8_slice_t *s, sort_compare_func_t sort_compare)
{
	if (s->len < 2) {
		return;
	}

	if (sort_compare == NULL) {
		return ;
	}

	qsort(s->items, s->len, sizeof(uint8_t), sort_compare);
}

uint64_t
uint8_slice_repeat(uint8_slice_t *s, const uint8_t val, const uint64_t times)
{
	for (uint64_t i = 0; i < times; i++) {
		uint8_slice_append(s, val);
	}

	return s->len;
}

uint64_t
uint8_slice_count(uint8_slice_t *s, const uint8_t val, compare_func_t compare)
{
	uint64_t count = 0;

	if (s->len == 0) {
		return count;
	}

	for (uint64_t i = 0; i < s->len; i++) {
		if (compare(s->items[i], val, NULL)) {
			count++;
		}
	}

	return count;
}

uint64_t
uint8_slice_grow(uint8_slice_t *s, const uint64_t size)
{
	if (size == 0) {
		return s->cap;
	}

	s->cap += size;
    s->items = realloc(s->items, sizeof(uint8_t) * s->cap);

	return s->cap;
}

uint64_t
uint8_slice_concat(uint8_slice_t *s1, const uint8_slice_t *s2)
{
	if (s2->len == 0) {
		return s1->len;
	}
	
	s1->cap += s2->len;
	s1->items = realloc(s1->items, sizeof(uint8_t) * s2->len);

	for (uint64_t i = 0, j = s1->len; i < s2->len; i++, j++) {
		s1->items[j] = s2->items[i];
		s1->len++;
	}
	
	return s1->len;
}
