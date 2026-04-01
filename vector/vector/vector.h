#ifndef TBC_VECTOR_H
#define TBC_VECTOR_H

#include <stddef.h>

typedef struct _vector *vector;

// Internal functions.
#ifndef TBC_VECTOR_INTERNAL
void* _vector_get(vector v, size_t index);
void  _vector_set(vector v, size_t index, void *elem);
void  _vector_push(vector v, void *elem);
vector _vector_init(size_t size, size_t cap);
#endif


// Create a new array with an optional initial capacity.
// Each element has size size.
// If cap == 0, a default capacity is chosen.
#define vector_init(type, cap) \
    _vector_init((sizeof (type)), (cap))

// Free the array and its storage.
void vector_free(vector v);

// Get the element at index.
// Returns NULL if out of bounds.
#define vector_get(v, index, type) \
    (*(type*)_vector_get((v), (index)))


// Set the element at index.
// If index >= current length, the array grows to fit.
#define vector_set(v, index, value) \
    do { typeof(value) _tmp = (value); _vector_set((v), (index), &_tmp); } while (0)

// Append an element to the end of the array.
#define vector_push(v, value) \
    do { typeof(value) _tmp = (value); _vector_push((v), &_tmp); } while (0)


// Current number of elements.
size_t vector_len(vector v);

// Current capacity.
size_t vector_cap(vector v);

#endif // TBC_VECTOR_H

