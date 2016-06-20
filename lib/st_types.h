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

#ifndef __ST_OBJECTS_ST_TYPES_H__
#define __ST_OBJECTS_ST_TYPES_H__

#include <stdint.h>

typedef uintptr_t st_ptr_t;
typedef uint8_t st_bool_t;
typedef uint16_t st_size_t;
typedef uint8_t st_byte_t;
struct st_dict_s;
struct st_array_s;
typedef char * st_string_t;
typedef int32_t st_int_t;
typedef int64_t st_long_t;
typedef double st_float_t;

#define ST_BOOL(a) ((a)?((st_bool_t)1):((st_bool_t)0))
#define ST_SIZE(a) (st_size_t)(a)
#define ST_INT(a) (st_int_t)(a)
#define ST_LONG(a) (st_long_t)(a)
#define ST_FLOAT(a) (st_float_t)(a)

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef TRUE
#define TRUE ((st_bool_t)1)
#endif

#ifndef FALSE
#define FALSE ((st_bool_t)0)
#endif

#endif // __ST_OBJECTS_ST_TYPES_H__
