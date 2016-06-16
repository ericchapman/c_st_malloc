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

struct st_dict_s;
struct st_array_s;
typedef char * st_string_t;
typedef int32_t st_int_t;
typedef int64_t st_long_t;
typedef float st_float_t;

typedef enum
{
    DICT,
    ARRAY,
    STRING,
    INTEGER,
    LONG,
    BOOLEAN,
    FLOAT
} st_object_type_t;

typedef struct st_object_s
{
    st_object_type_t type;
    void *value;
} st_object_t;

st_object_t *st_object_new(st_malloc_t *malloc, st_object_type_t type, void *value);
void st_object_set(st_object_t *this, st_object_type_t type, void *value);

struct st_dict_s *st_object_get_dict(st_object_t *this);
struct st_array_s *st_object_get_array(st_object_t *this);
st_bool_t st_object_get_bool(st_object_t *this);
st_string_t st_object_get_string(st_object_t *this);
st_int_t st_object_get_int(st_object_t *this);
st_long_t st_object_get_long(st_object_t *this);
st_float_t st_object_get_float(st_object_t *this);

#endif // __ST_OBJECTS_ST_OBJECT_H__
