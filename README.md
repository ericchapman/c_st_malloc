# Static Objects
A lightweight object library for embedded C applications that don't use malloc or free.

## Overview
The purpose of this C library is to provide a mechanism to create higher level objects such
as arrays and dictionaries *without* the use of malloc and free.  This will allow embedded
applications that are targeted for very small memory footprints to complete higher level
tasks such as deserializing a packet, creating a data structure and then serializing it
into a packet, or storing values as arrays or dictionaries.  This programming pattern uses
a concept I am calling *static malloc* to achieve this.

Like conventional malloc, static malloc uses the concept of a *heap* to allocate objects,
but the difference it that it does not track each malloc individually.  It instead
continuously allocates from the heap until a *free* is called globally on the entire heap.
The programming model for this is as follows

 - An *st_malloc* object is created and initialized
 - The software creates a series of data objects
 - The objects are shared with some other piece of code
 - On the return, all of the objects are freed

This has the following advantages over conventional malloc/free

 - Multiple *st_malloc* objects can be created for different pieces of code
 - The allocation procedure is very fast (it is simply moving a pointer)
 - The free process is very fast (it is simply moving a pointer back to the beginning)

The disadvantages are

 - The entire heap is cleared at once so there is no granularity on what objects remain
 - The receiving piece of code must copy any objects that is needs since they will be
   destroyed upon return

It is important to note that the programmer must fully understand what they are doing in
order to design a system that takes advantage of this type of programming model.

## Objects

### st_malloc
An *st_malloc* object is created as follows

``` c
#include "st_malloc.h"

uint8_t _heap[HEAPSIZE];

inf main()
{
    st_malloc st_m;
    st_malloc *st_m_p = &st_m;
    st_malloc_init(st_m_p, _heap, sizeof(_heap));

    return 0;
}
```

Some notes

 - The *_heap* attribute should be created globally so that it is declared in the ".data" region and
   not on the stack
 - The *HEAPSIZE* needs to be large enough to handle the largest that this data structure will get
   (just like a conventional *heap*)

*st_malloc* provides the following methods for allocating memory.  They differ in the alignment that
they use when allocating the requested block.  They are defined as follows

 - *void \*st_malloc_bytes(st_malloc_t \*this, uint16_t size)* - No alignment
 - *void \*st_malloc_var(st_malloc_t \*this, uint8_t size)* - Aligns to the size of hte variable
 - *void \*st_malloc_struct(st_malloc_t \*this, uint16_t size)* - Aligns to the size of a pointer in
   the target architecture

All objects that are allocated using these calls will be pulled from the head of the *st_malloc* object.

### st_object
An *st_object* is a container object that is used to encapsulate variables of the following types

 - st_bool_t - A boolean
 - st_int_t - A 32-bit integer
 - st_long_t - A 64-bit integer
 - st_float_t - A double float
 - st_string_t - A C string
 - st_array_t - An array implementation built on st_object
 - st_dict_t - A dictionary implementation built on st_object

 This object provides many accessors for the different types of values.  Below is an example of creating
 an integer *st_object*

 ``` c
    st_int_t *value = st_malloc_var(st_m_p, sizeof(st_int_t));
    *value = 25;
    st_object_t object = st_object_new(st_m_p, ST_OBJECT_TYPE_INT, value);

    if (st_object_get_int(object) != 25)
    {
        // TODO: Test Fail
    }
 ```

 ### st_array
 An *st_array* creates an ordered linked list of *st_object*s

 TODO

 ### st_dict
 An *st_dict* creates a key/value map of *st_object*s.  Note that is it not a hash table.  It simply searches an
 underlying array for the appropriate key.  This is slower doing lookups but a much lighter implementation than a
 full hash table.

 TODO

 ### Usage
 As described in the overview section, this library has a very specific use case.  If this coding style is not
 sufficient for your application, then you may need to consider using a full malloc/free library.