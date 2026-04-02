#ifndef TBC_MAP_H
#define TBC_MAP_H

#include <stddef.h>

typedef struct _hashmap *hashmap;

// Internal functions.
hashmap _map_init(size_t key_size, size_t val_size, size_t cap);
void _map_set(hashmap m, void *key, void *val);
void* _map_get(hashmap m, void *key);

// Public API
#define map_init(K, V, cap) \
    _map_init(sizeof(K), sizeof(V), (cap))

#define map_set(m, key, val) \
    _map_set((m), (key), (val))

#define map_get(m, key) \
    _map_get((m), (key))


void map_free(hashmap m);
size_t map_len(hashmap m);
size_t map_cap(hashmap m);


#endif // TBC_MAP_H

