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
#include <string.h>
#include "../lib/st_object.h"

static int errors = 0;
static int passes = 0;

static uint8_t _heap[256];
static st_malloc_t _st_m;

static void object_compare(st_object_t *object1, st_object_t *object2, st_bool_t expected)
{
    if (st_object_compare(object1, object2) != expected)
    {
        printf("object compare != %d and was supposed to\n", expected);
        errors++;
    }
    else
    {
        passes++;
    }
}

static void test_boolean() {
    st_object_t *object1, *object2;
    st_bool_t *value1, *value2;
    st_malloc_t *st_m = &_st_m;

    st_malloc_init(st_m, _heap, sizeof(_heap));

    value1 = st_malloc_var(st_m, sizeof(st_bool_t));
    value2 = st_malloc_var(st_m, sizeof(st_bool_t));
    object1 = st_object_new(st_m, ST_OBJECT_TYPE_BOOL, value1);
    object2 = st_object_new(st_m, ST_OBJECT_TYPE_BOOL, value2);

    object_compare(object1, object1, TRUE);

    *value1 = TRUE;
    *value2 = TRUE;
    object_compare(object1, object2, TRUE);

    *value1 = TRUE;
    *value2 = FALSE;
    object_compare(object1, object2, FALSE);

    if (st_object_get_bool(object1) != TRUE)
    {
        printf("object1 was expected to be TRUE but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

static void test_integer() {
    st_object_t *object1, *object2;
    st_int_t *value1, *value2;
    st_malloc_t *st_m = &_st_m;

    st_malloc_init(st_m, _heap, sizeof(_heap));

    value1 = st_malloc_var(st_m, sizeof(st_int_t));
    value2 = st_malloc_var(st_m, sizeof(st_int_t));
    object1 = st_object_new(st_m, ST_OBJECT_TYPE_INT, value1);
    object2 = st_object_new(st_m, ST_OBJECT_TYPE_INT, value2);

    object_compare(object1, object1, TRUE);

    *value1 = 22;
    *value2 = 22;
    object_compare(object1, object2, TRUE);

    *value1 = 22;
    *value2 = -22;
    object_compare(object1, object2, FALSE);

    if (st_object_get_int(object1) != 22)
    {
        printf("object1 was expected to be 22 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

static void test_long() {
    st_object_t *object1, *object2;
    st_long_t *value1, *value2;
    st_malloc_t *st_m = &_st_m;

    st_malloc_init(st_m, _heap, sizeof(_heap));

    value1 = st_malloc_var(st_m, sizeof(st_long_t));
    value2 = st_malloc_var(st_m, sizeof(st_long_t));
    object1 = st_object_new(st_m, ST_OBJECT_TYPE_LONG, value1);
    object2 = st_object_new(st_m, ST_OBJECT_TYPE_LONG, value2);

    object_compare(object1, object1, TRUE);

    *value1 = 22;
    *value2 = 22;
    object_compare(object1, object2, TRUE);

    *value1 = 22;
    *value2 = -22;
    object_compare(object1, object2, FALSE);

    if (st_object_get_long(object1) != 22)
    {
        printf("object1 was expected to be 22 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

static void test_float() {
    st_object_t *object1, *object2;
    st_float_t *value1, *value2;
    st_malloc_t *st_m = &_st_m;

    st_malloc_init(st_m, _heap, sizeof(_heap));

    value1 = st_malloc_var(st_m, sizeof(st_float_t));
    value2 = st_malloc_var(st_m, sizeof(st_float_t));
    object1 = st_object_new(st_m, ST_OBJECT_TYPE_FLOAT, value1);
    object2 = st_object_new(st_m, ST_OBJECT_TYPE_FLOAT, value2);

    object_compare(object1, object1, TRUE);

    *value1 = 22.1;
    *value2 = 22.1;
    object_compare(object1, object2, TRUE);

    *value1 = 22.1;
    *value2 = -22.1;
    object_compare(object1, object2, FALSE);

    if (st_object_get_float(object1) != 22.1)
    {
        printf("object1 was expected to be 22.1 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

static void test_string() {
    st_object_t *object1, *object2;
    st_malloc_t *st_m = &_st_m;

    st_malloc_init(st_m, _heap, sizeof(_heap));

    object1 = st_object_new(st_m, ST_OBJECT_TYPE_STR, "test");
    object2 = st_object_new(st_m, ST_OBJECT_TYPE_STR, "test");

    object_compare(object1, object1, TRUE);
    object_compare(object1, object2, TRUE);

    object2 = st_object_new(st_m, ST_OBJECT_TYPE_STR, "test1");
    object_compare(object1, object2, FALSE);

    if (strcmp(st_object_get_string(object1), "test") != 0)
    {
        printf("object1 was expected to be 'test' but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }
}

int test_st_object() {

    printf("\nRunning 'st_object' test\n");

    test_boolean();
    test_integer();
    test_long();
    test_float();
    test_string();

    if (errors == 0) {
        printf("Test passed with '%d' passes\n", passes);
    }
    else {
        printf("Test failed with '%d' errors\n", errors);
    }

    return errors;
}
