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

#ifndef __ST_OBJECTS_ST_OBJECT_H__
#define __ST_OBJECTS_ST_OBJECT_H__

#include "st_malloc.h"

typedef enum
{
    ST_OBJECT_TYPE_DICT,
    ST_OBJECT_TYPE_ARRAY,
    ST_OBJECT_TYPE_STR,
    ST_OBJECT_TYPE_INT,
    ST_OBJECT_TYPE_LONG,
    ST_OBJECT_TYPE_BOOL,
    ST_OBJECT_TYPE_FLOAT
} st_object_type_t;

typedef struct st_object_s
{
    st_object_type_t type;
    void *value;
} st_object_t;

st_object_t *st_object_new(st_malloc_t *malloc, st_object_type_t type, void *value);
void st_object_set(st_object_t *this, st_object_type_t type, void *value);

st_object_t *st_object_new_bool(st_malloc_t *malloc, st_bool_t value);
st_object_t *st_object_new_int(st_malloc_t *malloc, st_int_t value);
st_object_t *st_object_new_long(st_malloc_t *malloc, st_long_t value);
st_object_t *st_object_new_float(st_malloc_t *malloc, st_float_t value);
st_object_t *st_object_new_string(st_malloc_t *malloc, st_string_t value);
st_object_t *st_object_new_array(st_malloc_t *malloc, struct st_array_s *value);
st_object_t *st_object_new_dict(st_malloc_t *malloc, struct st_dict_s *value);

st_bool_t st_object_get_bool(st_object_t *this);
st_int_t st_object_get_int(st_object_t *this);
st_long_t st_object_get_long(st_object_t *this);
st_float_t st_object_get_float(st_object_t *this);
st_string_t st_object_get_string(st_object_t *this);
struct st_array_s *st_object_get_array(st_object_t *this);
struct st_dict_s *st_object_get_dict(st_object_t *this);

st_bool_t st_object_compare(st_object_t *object1, st_object_t *object2);

#endif // __ST_OBJECTS_ST_OBJECT_H__
