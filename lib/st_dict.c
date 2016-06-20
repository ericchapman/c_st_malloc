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

#include "st_dict.h"

st_dict_t *st_dict_new(st_malloc_t *malloc)
{
    st_dict_t *dict = st_malloc_struct(malloc, sizeof(st_dict_t));
    dict->malloc = malloc;
    st_dict_init(dict);
    return dict;
}

void st_dict_init(st_dict_t *this)
{
    this->array = st_array_new(this->malloc);
}

uint16_t st_dict_get_size(st_dict_t *this)
{
    return st_array_get_size(this->array);
}

st_bool_t st_dict_set_object(st_dict_t *this, st_object_t *key, st_object_t *object)
{
    st_link_t *new_link = st_link_new(this->malloc, object, key);
    st_dict_remove_object(this, key);
    return st_array_append_link(this->array, new_link);
}

st_bool_t st_dict_has_key(st_dict_t *this, st_object_t *key)
{
    return st_array_has_key(this->array, key);
}

st_object_t *st_dict_get_object(st_dict_t *this, st_object_t *key)
{
    uint16_t i;
    st_link_t *cur_link;

    for(i=0; i<st_array_get_size(this->array); i++)
    {
        cur_link = st_array_get_link(this->array, i);
        if (st_object_compare(key, cur_link->key))
        {
            return cur_link->object;
        }
    }

    return NULL;
}

st_bool_t st_dict_remove_object(st_dict_t *this, st_object_t *key)
{
    uint16_t i;
    st_link_t *cur_link;

    for(i=0; i<st_array_get_size(this->array); i++)
    {
        cur_link = st_array_get_link(this->array, i);
        if (st_object_compare(key, cur_link->key))
        {
            st_array_remove_link(this->array, i);
            return TRUE;
        }
    }
    return FALSE;
}