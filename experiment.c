#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "slice.h"

int
main(void)
{
    slice_t *grades = slice_new(S_UINT, 10);
    printf("Len: %" PRIu64 "\n", slice_len(grades));
    printf("Cap: %" PRIu64 "\n", slice_cap(grades));
    
    unsigned int grade = 100;

    slice_append(grades, grade);
    printf("Len: %" PRIu64 "\n", slice_len(grades));
    printf("Cap: %" PRIu64 "\n", slice_cap(grades));

    unsigned int g1 = slice_get(grades, 0);
    printf("Len: %" PRIu64 "\n", slice_len(grades));
    printf("Cap: %" PRIu64 "\n", slice_cap(grades));

    return 0;
}
