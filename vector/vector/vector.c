#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"

#define TBC_VECTOR_DEFAULT_CAP 64

struct _vector {
    size_t size;
    size_t len;
    size_t cap;
    unsigned char* data;
};

vector vector_init(size_t size, size_t cap) {
    vector v = malloc(sizeof (*v));
    v->size = size;
    v->len = 0;
    v->cap = cap ? cap : TBC_VECTOR_DEFAULT_CAP;
    v->data = calloc(v->cap, size);
    return v;
}

void vector_free(vector v) {
    free(v->data);
    free(v);
}

void vector_grow(vector v, size_t min_cap) {
    while (v->cap < min_cap) {
        v->cap *= 2;
    }
    v->data = reallocarray(v->data, v->cap, v->size);
}

void* vector_get(vector v, size_t index) {
    if (index >= v->len) return NULL;
    return v->data + index * v->size;
}

void vector_set(vector v, size_t index, void *elem) {
    if (index + 1 > v->cap) {
        vector_grow(v, index + 1);
    }
    memcpy(v->data + index * v->size, elem, v->size);
    if (index + 1 > v->len) {
        v->len = index + 1;
    }

}

void vector_push(vector v, void *elem) {
    if (v->len >= v->cap) vector_grow(v, v->len+1);
    memcpy(v->data + v->len * v->size, elem, v->size);
    v->len++;
}


size_t vector_len(vector v) {
    return v->len;
}

size_t vector_cap(vector v) {
    return v->cap;
}
