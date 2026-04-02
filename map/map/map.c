#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "map.h"

#define TBC_MAP_DEFAULT_CAP 64

struct _hashmap {
    size_t key_size;
    size_t val_size;
    size_t len;
    size_t cap;
    unsigned char *keys;
    unsigned char *vals;
    unsigned char *occupied; // bitmap or byte array
};


hashmap _map_init(size_t key_size, size_t val_size, size_t cap) {
    hashmap m = malloc(sizeof (*m));
    m->len = 0;
    m->cap = cap ? cap : TBC_MAP_DEFAULT_CAP;
    m->key_size = key_size;
    m->val_size = val_size;
    m->keys = calloc(m->cap, key_size);
    m->vals = calloc(m->cap, val_size);
    m->occupied = calloc(m->cap, 1);    // A bit wasteful to use entire byte.
    return m;
}


void map_free(hashmap m) {
    free(m->keys);
    free(m->vals);
    free(m->occupied);
    free(m);
}


uint64_t hash(const void *data, size_t size) {
    uint64_t h = 1469598103934665603ULL;
    const unsigned char *p = data;

    for (size_t i = 0; i < size; i++) {
        h ^= p[i];
        h *= 1099511628211ULL;
    }

    return h;
}



void _map_set(hashmap m, void *key, void *val) {
    int bucket = hash(key, m->key_size) % m->cap;

    for (size_t i = 0; i < m->cap; i++) {
        size_t idx = (bucket + i) % m->cap;

        // empty slot -> insert
        if (!m->occupied[idx]) {
            unsigned char *k_offset = m->keys + (idx * m->key_size);
            unsigned char *v_offset = m->vals + (idx * m->val_size);
            memcpy(k_offset, key, m->key_size);
            memcpy(v_offset, val, m->val_size);
            m->occupied[idx] = 1;
            m->len++;
            return;
        }

        // found -> overwrite
        if (memcmp(m->keys + idx * m->key_size, key, m->key_size) == 0) {
            memcpy(m->vals + (idx * m->val_size), val, m->val_size);
            return;
        }
    }
}

void* _map_get(hashmap m, void *key) {
    int bucket = hash(key, m->key_size) % m->cap;
    for (size_t i = 0; i < m->cap; i++) {
        size_t idx = (bucket + i) % m->cap;
        if (!m->occupied[idx]) return NULL;
        if (memcmp(m->keys + idx * m->key_size, key, m->key_size) == 0)
            return m->vals + idx * m->val_size;
    }
    return NULL;
}


size_t map_len(hashmap m) {
    return m->len;
}


size_t map_cap(hashmap m) {
    return m->cap;

}
