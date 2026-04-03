//! bitarray: A dynamic array of bits.
//!
//! Provides simple operations for setting, clearing,
//! and reading individual bits. Bits are stored LSB-first
//! within each byte.

#ifndef TBC_BITARRAY_H
#define TBC_BITARRAY_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _bitarray * bitarray;

/// Create a new bitarray with `count` bits.
/// @param count Number of bits.
/// @return A new bitarray.
bitarray bitarray_init(size_t count);

/// Free a bitarray.
/// @param b The bitarray to free.
void bitarray_destroy(bitarray b);

/// Set bit n.
/// @param b The bitarray.
/// @param n The bit index.
/// @return The previous value of the bit.
bool set(bitarray b, size_t n);

/// Clear bit n.
/// @param b The bitarray.
/// @param n The bit index.
/// @return The previous value of the bit.
bool clear(bitarray b, size_t n);

/// Read bit n.
/// @param b The bitarray.
/// @param n The bit index.
/// @return True if the bit is set.
bool get(bitarray b, size_t n);

/// Returns the length (count) of a bitarray.
/// @param b The bitarray.
/// @return Number of bits.
size_t bitarray_len(bitarray b);

#endif // TBC_BITARRAY_H
