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

#ifndef __ST_OBJECTS_ST_MALLOC_H__
#define __ST_OBJECTS_ST_MALLOC_H__

#include <stdint.h>

typedef uint8_t st_bool_t;
typedef uint16_t st_size_t;
typedef uint8_t st_byte_t;

#define ST_BOOL(a) ((a)?((st_bool_t)1):((st_bool_t)0))
#define ST_SIZE(a) (st_size_t)(a)

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef TRUE
#define TRUE ((st_bool_t)1)
#endif

#ifndef FALSE
#define FALSE ((st_bool_t)0)
#endif

typedef struct st_malloc_s
{
    st_byte_t *heap;
    st_byte_t *ptr;
    st_size_t size;
} st_malloc_t;

void st_malloc_init(st_malloc_t *this, st_byte_t *heap, st_size_t size);

/**
 * Allocates an array of bytes
 * @param this Pointer to the st_malloc instance
 * @param size The size of the bytes array to be allocated
 * @return Pointer to the byte array (or NULL)
 */
void *st_malloc_bytes(st_malloc_t *this, st_size_t size);

/**
 * Allocates a variable aligned to the size of the variable.
 * @param this Pointer to the st_malloc instance
 * @param size The size of the variable to be allocated
 * @return Pointer to the variable (or NULL)
 */
void *st_malloc_var(st_malloc_t *this, st_size_t size);

/**
 * Allocates a structure aligned to the size of "uintptr_t".
 * @param this Pointer to the st_malloc instance
 * @param size The size of the variable to be allocated
 * @return Pointer to the structure (or NULL)
 */
void *st_malloc_struct(st_malloc_t *this, st_size_t size);

/**
 * Returns "TRUE" if the buffer has overflowed
 * @param this Pointer to the st_malloc instance
 * @return "TRUE" if the buffer has overflowed
 */
st_bool_t st_malloc_did_overflow(st_malloc_t *this);

/**
 * Frees the ENTIRE heap
 * @param this Pointer to the st_malloc instance
 */
void st_malloc_free(st_malloc_t *this);

/**
 * Returns the number of bytes used in the heap
 * @param this Pointer to the st_malloc instance
 * @return Number of bytes used by the heap
 */
st_size_t st_malloc_used_bytes(st_malloc_t *this);

#endif // __ST_OBJECTS_ST_MALLOC_H__
