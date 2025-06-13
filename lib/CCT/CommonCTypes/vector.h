#ifndef _C_VECTOR_
#define _C_VECTOR_

#include <stddef.h>

#define EXIT_INVALID_ALLOCATON 214
// if you get this code, you kinda messed up. it can be from one of this functions:
// _cvec_pop
// _cvec_at
// _cvec_remove
// _cvec_insert

typedef struct vector {
    size_t cap;
    // cap is how much elements can be placed in vector without reallocating it  
    size_t byte_len;
    // byte_len is size of a single element in bytes (eg. 4 for 'int', 1 for 'char')
    size_t size;
    // size is how much elements are in vector
    void* start;
    // start is pointer to vector body (on heap, uses 'malloc')
} vector;

vector _cvec_new(size_t byte_len);
// returns an empty vector (0 size, 0 cap)

vector _cvec_new_filled(size_t size, size_t byte_len, const void* element);
// returns vector with 
// size and cap = "size"
// every element is copy of "element"

void _cvec_fill(vector* vec, const void* element);
// replaces every element in "vec" with copy of element

void _cvec_clear(vector* vec);
// sets vec size to 0 (capacity stays the same)

void _cvec_free(vector* vec);
// frees "vec->statr"

void _cvec_push(vector* vec, const void* element);
// pushes element on top of the "vec".

void _cvec_pop(vector* vec);
// removes last element of "vec" (cap stays the same)

void _cvec_reserve(vector* vec, size_t additional_size);
// add "additional_size" to "vec->cap" and reallocates

void* _cvec_at(vector* vec, size_t index);
// indexing value in the vector

void _cvec_realloc(vector* vec);
// used by other function.

void _cvec_reverse(vector* vec);
// reverses all elements of the "vec". reallocates

void _cvec_remove(vector* vec, size_t index);
// removes element by index

void _cvec_insert(vector* vec, const void* element, size_t index);
// inserts element by index

vector _cvec_clone(vector* vec);
// returns clone of the "vec" 

#endif // _C_VECTOR_