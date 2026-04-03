//! vector: A dynamically sized array of elements.
//!
//! Provides a simple, type-safe interface for storing arbitrary values.
//! Elements are stored contiguously and the array grows automatically
//! when needed.
//!
//! Example:<br>
//! <code>
//!     vector v = vector_init(int, 0);<br>
//!     vector_push(v, 42);<br>
//!     int x = vector_get(v, 0, int);<br>
//! </code>
//!
//! The underlying storage is managed automatically.

#ifndef TBC_VECTOR_H
#define TBC_VECTOR_H

#include <stddef.h>

typedef struct _vector *vector;

void* _vector_get(vector v, size_t index);
void  _vector_set(vector v, size_t index, void *elem);
void  _vector_push(vector v, void *elem);
vector _vector_init(size_t size, size_t cap);


/// Create a new vector with an optional initial capacity.
/// Each element has the size of `type`.
/// If cap == 0, a default capacity is chosen.
/// @decl vector vector_init(T type, size_t cap);
/// @param type The element type.
/// @param cap Initial capacity.
/// @return A new vector.
#define vector_init(type, cap) \
    _vector_init((sizeof (type)), (cap))

/// Free the vector and its storage.
/// @param v The vector to free.
void vector_free(vector v);


/// Get the element at index.
/// Returns the element cast to `type`.
/// Returns NULL if out of bounds.
/// @decl T vector_get(vector v, size_t index, T type);
/// @param v The vector.
/// @param index The element index.
/// @param type The element type.
/// @return The element at index.
#define vector_get(v, index, type) \
    (*(type*)_vector_get((v), (index)))


/// Set the element at index.
/// If index >= current length, the vector grows to fit.
/// @decl void vector_set(vector v, size_t index, T value);
/// @param v The vector.
/// @param index The element index.
/// @param value The value to store.
#define vector_set(v, index, value) \
    do { typeof(value) _tmp = (value); _vector_set((v), (index), &_tmp); } while (0)


/// Append an element to the end of the vector.
/// @decl void vector_push(vector v, T value);
/// @param v The vector.
/// @param value The value to append.
#define vector_push(v, value) \
    do { typeof(value) _tmp = (value); _vector_push((v), &_tmp); } while (0)


/// Current number of elements.
/// @param v The vector.
/// @return Number of elements.
size_t vector_len(vector v);

/// Current capacity.
/// @param v The vector.
/// @return Allocated capacity.
size_t vector_cap(vector v);

#endif // TBC_VECTOR_H
