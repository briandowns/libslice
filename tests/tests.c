#include "crosscheck.h"
#include "../int_slice.h"
#include "../int8_slice.h"
#include "../int16_slice.h"
#include "../int32_slice.h"
#include "../int64_slice.h"
#include "../uint_slice.h"
#include "../uint8_slice.h"
#include "../uint16_slice.h"
#include "../uint32_slice.h"
#include "../uint64_slice.h"
#include "../uint64_slice.h"

void
cc_setup(){}

void
cc_tear_down(){}

cc_result_t
test_int_slice_new()
{
    int_slice_t *is = int_slice_new(100);
    CC_ASSERT_NOT_NULL(is);
    int_slice_free(is);

    CC_SUCCESS;
}

int
main(void)
{
    CC_INIT;

    CC_RUN(test_int_slice_new);

    CC_COMPLETE;
}