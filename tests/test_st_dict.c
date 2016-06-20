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
#include "../lib/st_dict.h"

static int errors = 0;
static int passes = 0;

static uint8_t _heap[1024];

int test_st_dict() {
    st_dict_t *temp_dict;
    st_object_t *temp_object, *temp_key;

    st_malloc_t st_m;
    st_malloc_init(&st_m, _heap, sizeof(_heap));

    printf("\nRunning 'st_dict' test\n");

    // Create the dictionary
    temp_dict = st_dict_new(&st_m);

    // Insert the first value
    temp_object = st_object_new_int(&st_m, 25);
    temp_key = st_object_new_string(&st_m, "param1");
    st_dict_set_object(temp_dict, temp_key, temp_object);

    if (st_dict_get_size(temp_dict) != 1)
    {
        printf("Dict size was expected to be 1 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }

    temp_object = st_dict_get_object(temp_dict, temp_key);

    if (st_object_get_int(temp_object) != 25)
    {
        printf("Value was expected to be 25 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }

    temp_key = st_object_new_string(&st_m, "param1");

    if (st_dict_has_key(temp_dict, temp_key) != TRUE)
    {
        printf("Dict should have had key\n");
        errors++;
    }
    else
    {
        passes++;
    }

    temp_key = st_object_new_string(&st_m, "param2");

    if (st_dict_has_key(temp_dict, temp_key) != FALSE)
    {
        printf("Dict should not have had key\n");
        errors++;
    }
    else
    {
        passes++;
    }

    // Overwrite the value
    temp_object = st_object_new_int(&st_m, 28);
    temp_key = st_object_new_string(&st_m, "param1");
    st_dict_set_object(temp_dict, temp_key, temp_object);

    if (st_dict_get_size(temp_dict) != 1)
    {
        printf("Dict size was expected to be 1 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }

    temp_object = st_dict_get_object(temp_dict, temp_key);

    if (st_object_get_int(temp_object) != 28)
    {
        printf("Value was expected to be 25 but was not\n");
        errors++;
    }
    else
    {
        passes++;
    }

    // Remove the value
    st_dict_remove_object(temp_dict, temp_key);

    if (st_dict_get_size(temp_dict) != 0)
    {
        printf("Dict size was expected to be 0 but was not\n");
        errors++;
    }
    else
    {
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
