#ifndef TBC_VECTOR_H
#define TBC_VECTOR_H

#include <stddef.h>

typedef struct _vector *vector;

// Create a new array with an optional initial capacity.
// Each element has size size.
// If cap == 0, a default capacity is chosen.
vector vector_init(size_t size, size_t cap);

// Free the array and its storage.
void vector_free(vector v);

// Get the element at index.
// Returns NULL if out of bounds.
void* vector_get(vector v, size_t index);

// Set the element at index.
// If index >= current length, the array grows to fit.
void vector_set(vector v, size_t index, void *elem);

// Append an element to the end of the array.
void vector_push(vector v, void *elem);

// Current number of elements.
size_t vector_len(vector v);

// Current capacity.
size_t vector_cap(vector v);

#endif // TBC_VECTOR_H

