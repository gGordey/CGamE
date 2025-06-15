#include "vector.h"

#include <memory.h>
#include <malloc.h>
#include <stdlib.h>
#include <stddef.h>



vector _cvec_new(size_t byte_len) {
    vector vec;
    vec.byte_len = byte_len;
    vec.start = NULL;
    vec.size = 0;
    vec.cap = 0;
    return vec;
}
vector _cvec_new_filled(size_t size, size_t byte_len, const pvoid_t element) {
    vector vec = _cvec_new(byte_len);
    _cvec_reserve(&vec, size);
    for (size_t i = 0; i < size; ++i) {
        _cvec_push(&vec, element);
    }
    return vec;
}
void _cvec_fill(vector* vec, const pvoid_t element) {
    for (size_t i = 0; i < vec->size; ++i) {
        memcpy (
            vec->start + (i * vec->byte_len),
            element,
            vec->byte_len
        );
    }
}
void _cvec_clear(vector* vec) {
    vec->size = 0;
}
void _cvec_free(vector* vec) {
    free(vec->start);
    vec = NULL;
}
void _cvec_push(vector* vec, const pvoid_t element) {
    if (vec->size == vec->cap) {
        ++vec->cap;
        _cvec_realloc(vec);
    }
    memcpy (
        vec->start+(vec->byte_len * vec->size), 
        element, 
        vec->byte_len
    );
    ++vec->size;
}
void _cvec_pop(vector* vec) {
    if (vec->size <= 0) {
        exit(EXIT_INVALID_ALLOCATON);
    }
    --vec->size;
}
void _cvec_reserve(vector* vec, size_t additional) {
    if (additional <= 0)  { return; }
    vec->cap += additional;
    _cvec_realloc(vec);
}
pvoid_t _cvec_at(vector* vec, size_t ind) {
    if (ind >= vec->size || ind < 0) {
        exit(EXIT_INVALID_ALLOCATON);
    }
    return vec->start+(ind*vec->byte_len);
}
void _cvec_realloc(vector* vec) {
    pvoid_t copy_buf = malloc(vec->cap * vec->byte_len);
    memcpy (
        copy_buf, 
        vec->start, 
        (vec->size) * vec->byte_len
    );
    free(vec->start);
    vec->start = copy_buf;
}
void _cvec_reverse(vector* vec) {
    pvoid_t buffer = malloc(vec->cap * vec->byte_len);
    for (size_t i = vec->size; i >= 0; --i) {
        memcpy (
                buffer+((vec->size - i-1) * vec->byte_len), 
                vec->start + (i * vec->byte_len),
                vec->byte_len
            );
    }
    free(vec->start);
    vec->start = buffer;
}
void _cvec_remove(vector* vec, size_t ind) {
    if (vec->size <= 0 ) {
        return;
    }
    if (ind < 0 || ind >= vec->size) {
        exit(EXIT_INVALID_ALLOCATON);
    }
    if (ind == vec->size - 1) {
        _cvec_pop(vec);
        return;
    }
    else {
        memcpy (
                vec->start + (ind * vec->byte_len),
                vec->start + ((ind+1) * vec->byte_len),
                (vec->size - ind) * vec->byte_len
            );
        --vec->size;
    }
}
void _cvec_insert(vector* vec, const pvoid_t element, size_t ind) {
    if (ind < 0 || ind > vec->size) {
        exit(EXIT_INVALID_ALLOCATON);
    }
    if (ind == vec->size) {
        _cvec_push(vec, element);
        return;
    }
    if (vec->size == vec->cap) {
        ++vec->cap;
    }
    pvoid_t buf = malloc(vec->cap * vec->byte_len);
    if (ind > 0) {
        memcpy (
            buf,
            vec->start,
            ind * vec->byte_len
        );
    }
    memcpy (
        buf + (ind * vec->byte_len),
        element,
        vec->byte_len
    );
    memcpy (
        buf + ((ind+1) * vec->byte_len),
        vec->start + (ind * vec->byte_len),
        (vec->size - ind) * vec->byte_len
    );
    free(vec->start);
    vec->start = buf;
    ++vec->size;
}
vector _cvec_clone(vector* vec) {
    vector nv;
    nv.byte_len = vec->byte_len;
    nv.cap = vec->cap;
    nv.size = vec->size;
    nv.start = malloc(nv.cap * nv.byte_len);
    memcpy (
        nv.start, 
        vec->start, 
        nv.size * nv.byte_len
    );
    return nv;
}