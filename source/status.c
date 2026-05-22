#include "status.h"

#if defined (__STDC_HOSTED__)
#include <stdlib.h>
#else
#include "freestanding.h"
#endif

const char *const libvec_status_to_string(const enum libvec_status status)
{
    switch (status) {
        case LVSTAT_SUCCESS:
            return "Success";
        case LVSTAT_INVALID_ARGUMENT:
            return "Invalid argument";
        case LVSTAT_OUT_OF_MEMORY:
            return "Out of memory";
        case LVSTAT_EMPTY:
            return "Empty";
        case LVSTAT_INDEX_OUT_OF_BOUNDS:
            return "Index out of bounds";
        case LVSTAT_ALLOCATION_FAILURE:
            return "Allocation failure";
        default:
            return "Invalid status code";
    }
}