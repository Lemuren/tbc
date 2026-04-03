#include <stdlib.h>
#include <stdint.h>
#include "bitarray.h"

struct _bitarray {
    size_t len;
    uint8_t *data;
};

bitarray bitarray_init(size_t count) {
    struct _bitarray *b = malloc(sizeof(*b));
    b->len = count;
    b->data = calloc(((count + 7) / 8), sizeof(uint8_t));
    return b;
}

void bitarray_destroy(bitarray b) {
    free(b->data);
    free(b);
}

bool set(bitarray b, size_t n) {
    bool old = get(b, n);
    b->data[n / 8] = b->data[n / 8] | (1UL << (n % 8));
    return old;
}

bool clear(bitarray b, size_t n) {
    bool old = get(b, n);
    b->data[n / 8] = b->data[n / 8] & ~(1UL << (n % 8));
    return old;
}

bool get(bitarray b, size_t n) {
    return ((b->data[n / 8]) >> (n % 8)) & 1UL;
}

size_t bitarray_len(bitarray b) {
    return b->len;
}
