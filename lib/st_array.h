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

#ifndef __ST_OBJECTS_ST_ARRAY_H__
#define __ST_OBJECTS_ST_ARRAY_H__

#include "st_link.h"

typedef struct st_array_s
{
    st_link_t *first;
    st_link_t *last;
    uint16_t size;
    st_malloc_t *malloc;
} st_array_t;

st_array_t *st_array_new(st_malloc_t *malloc);
void st_array_init(st_array_t *this);

uint16_t st_array_get_size(st_array_t *this);

st_bool_t st_array_insert_link(st_array_t *this, st_link_t *link, uint16_t index);
st_link_t *st_array_get_link(st_array_t *this, uint16_t index);
st_bool_t st_array_remove_link(st_array_t *this, uint16_t index);
st_bool_t st_array_has_link(st_array_t *this, st_link_t *link);

st_bool_t st_array_insert_object(st_array_t *this, st_object_t *object, uint16_t index);
st_bool_t st_array_append_object(st_array_t *this, st_object_t *object);
st_object_t *st_array_get_object(st_array_t *this, uint16_t index);
st_bool_t st_array_remove_object(st_array_t *this, uint16_t index);
st_bool_t st_array_has_object(st_array_t *this, st_object_t *object);

#endif // __ST_OBJECTS_ST_ARRAY_H__
