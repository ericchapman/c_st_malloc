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
#include "../lib/st_array.h"

static uint8_t _heap[1024];

static int errors = 0;
static int passes = 0;

void compare_link_value(st_array_t *array, int index, int value)
{
    st_link_t *temp_link = st_array_get_link(array, (uint16_t)index);
    if (st_object_get_int(temp_link->object) != value)
    {
        printf("object value != %d and was supposed to\n", value);
        errors++;
    }
    else
    {
        passes++;
    }

}

void compare_object_value(st_array_t *array, int index, int value)
{
    st_object_t *temp_object = st_array_get_object(array, (uint16_t)index);
    if (st_object_get_int(temp_object) != value)
    {
        printf("object value != %d and was supposed to\n", value);
        errors++;
    }
    else
    {
        passes++;
    }

}

void compare_array_length(st_array_t *array, int size)
{
    if (st_array_get_size(array) != size)
    {
        printf("array size != %d and was supposed to\n", size);
        errors++;
    }
    else
    {
        passes++;
    }
}

void link_tests()
{
    int i;

    st_int_t *temp_int;
    st_array_t *temp_array;
    st_object_t *temp_object;
    st_link_t *temp_link;

    /* Create Malloc */
    st_malloc_t st_m;
    st_malloc_init(&st_m, _heap, sizeof(_heap));

    /* Create Array */
    temp_array = st_array_new(&st_m);

    /* Create as simple array of integers */
    for (i=0; i<5; i++)
    {
        temp_int = st_malloc_var(&st_m, sizeof(st_int_t));
        *temp_int = i+10;
        temp_object = st_object_new(&st_m, ST_OBJECT_TYPE_INT, temp_int);
        temp_link = st_link_new(&st_m, temp_object, NULL);
        st_array_insert_link(temp_array, temp_link, i);
    }

    compare_array_length(temp_array, 5);
    compare_link_value(temp_array, 0, 10);
    compare_link_value(temp_array, 1, 11);
    compare_link_value(temp_array, 2, 12);
    compare_link_value(temp_array, 3, 13);
    compare_link_value(temp_array, 4, 14);

    /* Remove the one of the middle links */
    st_array_remove_link(temp_array, 1);

    compare_array_length(temp_array, 4);
    compare_link_value(temp_array, 0, 10);
    compare_link_value(temp_array, 1, 12);
    compare_link_value(temp_array, 2, 13);
    compare_link_value(temp_array, 3, 14);

    /* Remove a different middle link */
    st_array_remove_link(temp_array, 2);

    compare_array_length(temp_array, 3);
    compare_link_value(temp_array, 0, 10);
    compare_link_value(temp_array, 1, 12);
    compare_link_value(temp_array, 2, 14);

    /* Remove the beginning one */
    st_array_remove_link(temp_array, 0);

    compare_array_length(temp_array, 2);
    compare_link_value(temp_array, 0, 12);
    compare_link_value(temp_array, 1, 14);

    /* Remove the end one */
    st_array_remove_link(temp_array, 1);

    compare_array_length(temp_array, 1);
    compare_link_value(temp_array, 0, 12);
}

void object_tests()
{
    int i;

    st_int_t *temp_int;
    st_array_t *temp_array;
    st_object_t *temp_object;

    /* Create Malloc */
    st_malloc_t st_m;
    st_malloc_init(&st_m, _heap, sizeof(_heap));

    /* Create Array */
    temp_array = st_array_new(&st_m);

    /* Create as simple array of integers */
    for (i=0; i<5; i++)
    {
        temp_int = st_malloc_var(&st_m, sizeof(st_int_t));
        *temp_int = i+10;
        temp_object = st_object_new(&st_m, ST_OBJECT_TYPE_INT, temp_int);
        st_array_insert_object(temp_array, temp_object, i);
    }

    compare_array_length(temp_array, 5);
    compare_object_value(temp_array, 0, 10);
    compare_object_value(temp_array, 1, 11);
    compare_object_value(temp_array, 2, 12);
    compare_object_value(temp_array, 3, 13);
    compare_object_value(temp_array, 4, 14);

    /* Remove the one of the middle links */
    st_array_remove_object(temp_array, 1);

    compare_array_length(temp_array, 4);
    compare_object_value(temp_array, 0, 10);
    compare_object_value(temp_array, 1, 12);
    compare_object_value(temp_array, 2, 13);
    compare_object_value(temp_array, 3, 14);

    /* Remove a different middle link */
    st_array_remove_object(temp_array, 2);

    compare_array_length(temp_array, 3);
    compare_object_value(temp_array, 0, 10);
    compare_object_value(temp_array, 1, 12);
    compare_object_value(temp_array, 2, 14);

    /* Remove the beginning one */
    st_array_remove_object(temp_array, 0);

    compare_array_length(temp_array, 2);
    compare_object_value(temp_array, 0, 12);
    compare_object_value(temp_array, 1, 14);

    /* Remove the end one */
    st_array_remove_object(temp_array, 1);

    compare_array_length(temp_array, 1);
    compare_object_value(temp_array, 0, 12);

    /* Append Object */
    temp_int = st_malloc_var(&st_m, sizeof(st_int_t));
    *temp_int = 14;
    temp_object = st_object_new(&st_m, ST_OBJECT_TYPE_INT, temp_int);
    st_array_append_object(temp_array, temp_object);

    compare_array_length(temp_array, 2);
    compare_object_value(temp_array, 0, 12);
    compare_object_value(temp_array, 1, 14);

    if (st_array_has_object(temp_array, temp_object) == FALSE)
    {
        printf("Array should have had object\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

int test_st_array()
{
    printf("\nRunning 'st_array' test\n");

    link_tests();
    object_tests();

    if (errors == 0) {
        printf("Test passed with '%d' passes\n", passes);
    }
    else {
        printf("Test failed with '%d' errors\n", errors);
    }

    return errors;
}
