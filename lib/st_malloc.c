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

#include "st_malloc.h"

static void _st_malloc_align(st_malloc_t *this, uint8_t size)
{
    while((uintptr_t)this->ptr%size != 0)
    {
        this->ptr++;
    }
}

static void *_st_malloc(st_malloc_t *this, uint16_t size)
{
    void *location = this->ptr;
    this->ptr += size;
    return (st_malloc_did_overflow(this))?NULL:location;
}

st_bool_t st_malloc_did_overflow(st_malloc_t *this)
{
    return (uint8_t)(((uintptr_t)this->ptr > ((uintptr_t)this->heap + this->size))?TRUE:FALSE);
}

void st_malloc_init(st_malloc_t *this, uint8_t *heap, uint16_t size)
{
    this->heap = heap;
    this->size = size;
    this->ptr = heap;
}

void *st_malloc_bytes(st_malloc_t *this, uint16_t size)
{
    return _st_malloc(this, size);
}

void *st_malloc_var(st_malloc_t *this, uint8_t size)
{
    _st_malloc_align(this, size);
    return _st_malloc(this, size);
}

void *st_malloc_struct(st_malloc_t *this, uint16_t size)
{
    _st_malloc_align(this, sizeof(uintptr_t));
    return _st_malloc(this, size);
}

void st_malloc_free(st_malloc_t *this)
{
    this->ptr = this->heap;
}

uint16_t st_malloc_used_bytes(st_malloc_t *this)
{
    return (uint16_t)((uintptr_t)this->ptr - (uintptr_t)this->heap);
}
