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

#include "st_array.h"

st_array_t *st_array_new(st_malloc_t *malloc)
{
    st_array_t *array = st_malloc_struct(malloc, sizeof(st_array_t));
    array->malloc = malloc;
    st_array_init(array);
    return array;
}

void st_array_init(st_array_t *this)
{
    this->first = NULL;
    this->last = NULL;
    this->size = 0;
}

uint16_t st_array_get_size(st_array_t *this)
{
    return this->size;
}

st_bool_t st_array_insert_link(st_array_t *this, st_link_t *link, uint16_t index)
{
    st_link_t *cur_link = st_array_get_link(this, index);

    if (cur_link == NULL) {
        // Append operation
        cur_link = this->last;
        link->prev = cur_link;
        link->next = NULL;
        this->last = link;

        // There are no links
        if (cur_link == NULL) {
            this->first = link;
        }
        else {
            cur_link->next = link;
        }
    }
    else {
        // Insert operation
        link->prev = cur_link->prev;
        link->next = cur_link;
        cur_link->prev = link;

        // This is the index 0 link
        if (link->prev == NULL) {
            this->first = link;
        }
        else {
            link->prev->next = link;
        }
    }

    this->size++;

    return TRUE;
}

st_bool_t st_array_remove_link(st_array_t *this, uint16_t index)
{
    st_link_t *cur_link = st_array_get_link(this, index);

    if (cur_link == NULL) {
        return FALSE;
    }

    if (cur_link->prev == NULL) {
        this->first = cur_link->next;
    }
    else {
        cur_link->prev->next = cur_link->next;
    }

    if (cur_link->next == NULL) {
        this->last = cur_link->prev;
    }
    else {
        cur_link->next->prev = cur_link->prev;
    }

    this->size--;

    return TRUE;
}

st_link_t *st_array_get_link(st_array_t *this, uint16_t index)
{
    st_link_t *cur_link;

    if (index >= st_array_get_size(this)) {
        return NULL;
    }

    cur_link = this->first;
    while(index > 0) {
        cur_link = cur_link->next;
        index--;
    }

    return cur_link;
}

st_bool_t st_array_has_link(st_array_t *this, st_link_t *link)
{
    int i;
    for(i=0; i<st_array_get_size(this); i++)
    {
        if (st_array_get_link(this, (uint16_t)i) == link) {
            return TRUE;
        }
    }

    return FALSE;
}

st_bool_t st_array_insert_object(st_array_t *this, st_object_t *object, uint16_t index)
{
    st_link_t *new_link = st_link_new(this->malloc, object, NULL);
    return st_array_insert_link(this, new_link, index);
}

st_bool_t st_array_append_object(st_array_t *this, st_object_t *object)
{
    st_link_t *new_link = st_link_new(this->malloc, object, NULL);
    return st_array_insert_link(this, new_link, st_array_get_size(this));
}

st_object_t *st_array_get_object(st_array_t *this, uint16_t index)
{
    st_link_t *link = st_array_get_link(this, index);
    return (link != NULL)?link->object:NULL;
}

st_bool_t st_array_remove_object(st_array_t *this, uint16_t index)
{
    return st_array_remove_link(this, index);
}

st_bool_t st_array_has_object(st_array_t *this, st_object_t *object)
{
    int i;
    st_link_t *link;
    for(i=0; i<st_array_get_size(this); i++)
    {
        link = st_array_get_link(this, (uint16_t)i);
        if (link != NULL && link->object == object) {
            return TRUE;
        }
    }

    return FALSE;
}
