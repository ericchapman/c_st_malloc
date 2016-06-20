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

#ifndef __ST_OBJECTS_ST_DICT_H__
#define __ST_OBJECTS_ST_DICT_H__

#include "st_array.h"

typedef struct st_dict_s
{
    st_array_t *array;
    st_malloc_t *malloc;
} st_dict_t;

st_dict_t *st_dict_new(st_malloc_t *malloc);
void st_dict_init(st_dict_t *this);

uint16_t st_dict_get_size(st_dict_t *this);
st_bool_t st_dict_set_object(st_dict_t *this, st_object_t *key, st_object_t *object);
st_bool_t st_dict_has_key(st_dict_t *this, st_object_t *key);
st_object_t *st_dict_get_object(st_dict_t *this, st_object_t *key);
st_bool_t st_dict_remove_object(st_dict_t *this, st_object_t *key);

#endif // __ST_OBJECTS_ST_DICT_H__
