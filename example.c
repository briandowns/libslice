#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "int_slice.h"

int
main(void)
{
    int_slice_t *s = int_slice_new(100);
    
    for (int i = 0; i < 10000; i++) {
        int_slice_append(s, i);
    }
    printf("%ld\n", int_slice_len(s));
    printf("%ld\n", int_slice_cap(s));

    int_slice_free(s);

    return 0;
}
