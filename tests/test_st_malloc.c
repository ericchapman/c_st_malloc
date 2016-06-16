/**

Copyright (c) 2016 Eric Chapman

MIT License

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <stdio.h>
#include "../lib/st_malloc.h"

int test_st_malloc()
{
    int errors = 0;
    int passes = 0;
    uint8_t *test_bytes;
    int16_t *test_integer;
    st_malloc_t *test_struct;

    /* Create Malloc */
    uint8_t heap[64];
    st_malloc_t st_m;
    st_malloc_init(&st_m, heap, 64);

    printf("\nRunning 'st_malloc' test\n");

    test_bytes = (uint8_t *)st_malloc_bytes(&st_m, 15);
    test_integer = (int16_t *)st_malloc_var(&st_m, sizeof(int16_t));
    test_struct = (st_malloc_t *)st_malloc_struct(&st_m, sizeof(st_malloc_t));

    printf("Testing mallocs and alignment...\n");

    if (test_bytes != heap)
    {
        errors++;
        printf("test_bytes != heap as expected\n");
    }
    else {
        passes++;
    }

    if ((uintptr_t)test_integer != (uintptr_t)heap+16)
    {
        errors++;
        printf("test_integer != heap+16 as expected\n");
    }
    else {
        passes++;
    }

    if ((uintptr_t)test_struct != (uintptr_t)heap+16+sizeof(uintptr_t))
    {
        errors++;
        printf("test_struct != heap+16+sizeof(uintptr_t) as expected\n");
    }
    else {
        passes++;
    }

    if (st_malloc_did_overflow(&st_m) != 0)
    {
        errors++;
        printf("did overflow != 0 as expected\n");
    }
    else {
        passes++;
    }

    printf("Testing free...\n");

    st_malloc_free(&st_m);

    if (st_m.ptr != st_m.heap)
    {
        errors++;
        printf("pointer != heap after free as expected\n");
    }
    else {
        passes++;
    }

    printf("Testing overflow...\n");

    test_bytes = (uint8_t *)st_malloc_bytes(&st_m, 64);

    if (st_malloc_used_bytes(&st_m) != 64)
    {
        errors++;
        printf("used bytes != 64 as expected\n");
    }
    else {
        passes++;
    }

    if (st_malloc_did_overflow(&st_m))
    {
        errors++;
        printf("did overflow was not FALSE as expected\n");
    }
    else {
        passes++;
    }

    test_bytes = (uint8_t *)st_malloc_bytes(&st_m, 1);

    if (!st_malloc_did_overflow(&st_m))
    {
        errors++;
        printf("did overflow was not TRUE as expected\n");
    }
    else {
        passes++;
    }

    if (test_bytes != NULL)
    {
        errors++;
        printf("test_bytes != NULL as expected\n");
    }
    else {
        passes++;
    }

    if (errors == 0) {
        printf("Test passed with '%d' passes\n", passes);
    }
    else {
        printf("Test failed with '%d' errors\n", errors);
    }

    return errors;
}
