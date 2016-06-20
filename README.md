# Static Objects
A lightweight object library for embedded C applications that don't use malloc or free.

## Overview
The purpose of this C library is to provide a mechanism to create higher level objects such
as arrays and dictionaries *without* the use of malloc and free.  This will allow embedded
applications that are targeted for very small memory footprints to complete higher level
tasks such as creating high level objects or serializing/deserializing a packet.  This
programming pattern uses a concept I am calling *static malloc* to achieve this.

Like conventional malloc, static malloc uses the concept of a *heap* to allocate objects,
but the difference is that it does not track each malloc individually.  It instead
continuously allocates from the heap until a *free* is called globally on the entire heap.
The programming model for this is as follows

 - An *st_malloc* object is created and initialized **once**
 - The software creates a series of data objects
 - The objects are shared with some other piece of code
 - On the return, all of the objects are freed

This has the following advantages over conventional malloc/free

 - Multiple *st_malloc* objects can be created for different pieces of code
 - The allocation procedure is very fast (it is simply moving a pointer)
 - The free process is very fast (it is simply moving a pointer back to the beginning)
 - You no longer have to worry about memory leaks since *free* will clear everything

The disadvantages are

 - The entire heap is cleared at once so there is no granularity on what objects remain
 - The receiving piece of code must copy any objects that is needs since they will be
   destroyed upon return

It is important to note that the programmer must fully understand what they are doing in
order to design a system that takes advantage of this type of programming model.  It is
only well suited for a particular use case which is building objects, sharing them, and
then destroying them.

## Objects

### st_malloc
An *st_malloc* object is created as follows

``` c
#include "st_malloc.h"

st_byte_t _heap[HEAPSIZE];

inf main()
{
    // Initialize the malloc object (do this once)
    st_malloc st_m;
    st_malloc_init(&st_m, _heap, sizeof(_heap));

    // Allocate 256 bytes
    st_string_t bytes = st_malloc_bytes(&st_m, 256);

    // Allocate an integer
    st_int_t *integer = st_malloc_var(&st_m, sizeof(st_int_t));
    *integer = 26;

    // Free all created objects
    st_malloc_free(&st_m);

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

``` c
void *st_malloc_bytes(st_malloc_t *this, st_size_t size);   // No alignment
void *st_malloc_var(st_malloc_t *this, st_size_t size);     // Aligns to the size of the variable
void *st_malloc_struct(st_malloc_t *this, st_size_t size);  // Aligns to the size of a pointer in the target architecture
```
All objects that are allocated using these calls will be pulled from the *heap* of the *st_malloc* object.
In order to free all of the objects, simply call

``` c
void st_malloc_free(st_malloc_t *this);
```

You can also check how much of the heap is allocated by calling the following method

``` c
st_size_t st_malloc_used_bytes(st_malloc_t *this);
```

Please see *st_malloc.h* for more methods that are available

### st_object
An *st_object* is a container object that is used to encapsulate variables of the following types

 - st_bool_t - A boolean
 - st_int_t - A 32-bit integer
 - st_long_t - A 64-bit integer
 - st_float_t - A double float
 - st_string_t - A C string
 - st_array_t - An array implementation built on st_object
 - st_dict_t - A dictionary implementation built on st_object

The *st_object* class has numerous creation methods that are used to create new objects.  They are as follows

``` c
st_object_t *st_object_new_bool(st_malloc_t *malloc, st_bool_t value);
st_object_t *st_object_new_int(st_malloc_t *malloc, st_int_t value);
st_object_t *st_object_new_long(st_malloc_t *malloc, st_long_t value);
st_object_t *st_object_new_float(st_malloc_t *malloc, st_float_t value);
st_object_t *st_object_new_string(st_malloc_t *malloc, st_string_t value);
st_object_t *st_object_new_array(st_malloc_t *malloc, struct st_array_s *value);
st_object_t *st_object_new_dict(st_malloc_t *malloc, struct st_dict_s *value);
```

Calling any of these will allocate that type of object from the *heap* and set it with the value.  Note that
the value is copied so any further manipulation of the passed in variable will be ignored.

The class provides getters for accessing the value.  The getters are defined as follows

``` c
st_bool_t st_object_get_bool(st_object_t *this);
st_int_t st_object_get_int(st_object_t *this);
st_long_t st_object_get_long(st_object_t *this);
st_float_t st_object_get_float(st_object_t *this);
st_string_t st_object_get_string(st_object_t *this);
struct st_array_s *st_object_get_array(st_object_t *this);
struct st_dict_s *st_object_get_dict(st_object_t *this);
```

As a convenience function, the class provides a *compare* method that will return *TRUE* if two
objects are considered equal.

``` c
st_bool_t st_object_compare(st_object_t *object1, st_object_t *object2);
```

Equality is defined as follows

 - *object* pointer is the same value for both objects, or
 - *type* is the same and
   - *value* pointer is the same (for array's and dict's)
   - Value of *value* is the same for all other object types

Please see *st_object.h* for more methods that are available

### st_array
An *st_array* creates an ordered linked list of *st_object*s.  It includes methods to operate on
the links of the list directly OR on the objects that are contained in the links.  the methods
for operating on the links are are follows

``` c
st_bool_t st_array_insert_link(st_array_t *this, st_link_t *link, uint16_t index);
st_bool_t st_array_append_link(st_array_t *this, st_link_t *link);
st_link_t *st_array_get_link(st_array_t *this, uint16_t index);
st_bool_t st_array_remove_link(st_array_t *this, uint16_t index);
```

The object manipulation methods are

``` c
st_bool_t st_array_insert_object(st_array_t *this, st_object_t *object, uint16_t index);
st_bool_t st_array_append_object(st_array_t *this, st_object_t *object);
st_object_t *st_array_get_object(st_array_t *this, uint16_t index);
st_bool_t st_array_remove_object(st_array_t *this, uint16_t index);
```

There are *has* methods that allow you to see if certain things are contained in the array.  They are

``` c
st_bool_t st_array_has_link(st_array_t *this, st_link_t *link);
st_bool_t st_array_has_object(st_array_t *this, st_object_t *object);
st_bool_t st_array_has_key(st_array_t *this, st_object_t *key);
```

Please see *st_array.h* for more methods that are available

### st_dict
An *st_dict* creates a key/value map of *st_object*s.  It uses the *st_array* object to store
the objects.  Note that this is not a hash table and when looking for a value based on *key*,
it must iterate over the entire array object until it finds the value.  This is slower than
a conventional hash table when there are many values in the dictionary BUT given the memory
footprint that this library targets, it is assumed that the dictionary will not have very many
values.

The following methods are defined

``` c
uint16_t st_dict_get_size(st_dict_t *this);
st_bool_t st_dict_set_object(st_dict_t *this, st_object_t *key, st_object_t *object);
st_bool_t st_dict_has_key(st_dict_t *this, st_object_t *key);
st_object_t *st_dict_get_object(st_dict_t *this, st_object_t *key);
st_bool_t st_dict_remove_object(st_dict_t *this, st_object_t *key);
```

Note that ANY *st_object* can be used as a *key*.  This is to provide flexibility in the use
of the dictionary.

Please see *st_dict.h* for more methods that are available

## Usage
Below is a snippet of code that illustrates the use of this library

``` c
#include "st_dict.h"

st_byte_t _heap[1024];

int main()
{
    st_malloc_t malloc;
    st_dict_t *dict;

    // Initialize the malloc object (do once)
    st_malloc_init(&malloc, _heap, sizeof(_heap));

    // Create the dictionary
    dict = st_dict_new(&malloc);

    // Create the key/value pair "param1" - 22.5 (float)
    st_dict_set_object(
        dict,
        st_object_new_string(&malloc, "param1"),  // key
        st_object_new_float(&malloc, 22.5)        // object
    );

    // Create the key/value pair 16.3 (float) - "value1"
    st_dict_set_object(
        dict,
        st_object_new_float(&malloc, 16.3),       // key
        st_object_new_string(&malloc, "value1")   // object
    );

    // Do something with the dictionary
    // ...

    // Destroy all of the objects
    st_malloc_free(&malloc);

    return 0;
}
```
