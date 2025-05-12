#include <stdint.h>
#include <stdlib.h>

#include "slice.h"

struct slice {
    uint64_t len;
    uint64_t cap;
    slice_type_t type;
    union {
        unsigned int *uint_items;
        uint8_t *uint8_items;
        uint16_t *uint16_items;
        uint32_t *uint32_items;
        uint64_t *uint64_items;
        int *int_items;
        int8_t *int8_items;
        int16_t *int16_items;
        int32_t *int32_items;
        int64_t *int64_items;
        size_t *size_t_items;
    };
};

slice_t*
slice_new(const slice_type_t type, const uint64_t cap)
{
    slice_t *s = calloc(1, sizeof(slice_t));

    switch (type) {
        case S_UINT:
            s->type = S_UINT;
            s->uint_items = calloc(1, sizeof(unsigned int) * cap);
            break;
        case S_UINT8:
            s->type = S_UINT8;
            s->uint8_items = calloc(1, sizeof(uint8_t) * cap);
            break;
        case S_UINT16:
            s->type = S_UINT8;
            s->uint16_items = calloc(1, sizeof(uint16_t) * cap);
            break;
    }
    s->len = 0;
    s->cap = cap;

    return s;
}

// void
// slice_free(slice_t *s) {
// 	if (s != NULL && s->items != NULL) {
//         free(s->items);
//         free(s);
// 	} 
// }

// int
// slice_get(slice_t *s, uint64_t idx)
// {
//     if (idx >= 0 && idx < s->len) {
//         return s->items[idx];
//     }

//     return 0;
// }

uint64_t
slice_len(slice_t *s)
{
	if (s == NULL) {
		return 0;
	}

	struct slice *is = (struct slice*)s;
	return is->len;
}

uint64_t
slice_cap(slice_t *s)
{
	if (s == NULL) {
		return 0;
	}

	struct slice *is = (struct slice*)s;
	return is->cap;	
}

void*
__slice_get(slice_t *s, uint64_t idx)
{
    if (idx >= 0 && idx < s->len) {
        switch (s->type) {
        case S_UINT:
            return (void*)&(s->uint_items[idx]);       
        }
    }

    return 0;
}

void
__slice_append(slice_t *s, const void *val)
{
    switch (s->type) {
        case S_UINT:
            if (s->len == s->cap) {
                s->cap *= 2;
                s->uint_items = realloc(s->uint_items, sizeof(unsigned int) * s->cap);
            }
            unsigned int v = *(unsigned int*)(val);
            s->uint_items[s->len++] = v;       
    }
}
