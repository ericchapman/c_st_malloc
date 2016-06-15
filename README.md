# Static Malloc

*st_malloc* is a lightweight C library intended to allow low level C programs to have some malloc/free
capabilities using a statically allocated buffer.  The limitation is that *free* is called globally on
**all** allocated values instead of each individual value.

The use case that this library is attempting to target is embedded applications executing on very small
memory footprints that do not have malloc/free but need the ability to temporarily create data structures
to pass information to receiving callbacks.  The receiving callback functions will copy what data they
need.  When the callback returns the caller that malloc-ed all of the objects will then call *free* which
will clear all allocated objects.

The implementation is very small and very fast.  The only real memory overhead is the size of the heap
itself.

## Usage

``` c
#include "st_malloc.h"

int main()
{
    /* Allocate a heap */
    uint8_t heap[256];

    /* Initialize an st_malloc instance */
    st_malloc_t st_malloc;
    st_malloc_init(&st_malloc, heap, 256);

    /* Allocate 10 bytes */
    uint8_t *bytes = st_malloc_bytes(&st_malloc, 10);

    /* Allocate an integer */
    int *integer = st_malloc_var(&st_malloc, sizeof(int));

    /* Allocate a structure of type "struct_t" */
    struct_t *structure = st_malloc_struct(&st_malloc, sizeof(struct_t));

    /* Free all allocations */
    st_malloc_free(&st_malloc);

    return 0;
}
```

The main difference between *_bytes*, *_var*, and *_struct* is the alignment of the allocation.  It is
described as follows

 - _bytes - No alignment
 - _var - Aligned to the size of the variable
 - _struct - Aligned to the size of *uintptr_t*

