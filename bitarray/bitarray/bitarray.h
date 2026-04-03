#ifndef TBC_BITARRAY_H
#define TBC_BITARRAY_H

#include <stddef.h>
#include <stdbool.h>

typedef struct _bitarray * bitarray;

// Create a new bitarray of count bits.
bitarray bitarray_init(size_t count);

// Free a bitarray.
void bitarray_destroy(bitarray b);

// Set bit n. Returns the value of the bit that was set.
bool set(bitarray b, size_t n);

// Clear bit n. Returns the value of the bit that was cleared.
bool clear(bitarray b, size_t n);

// Read bit n.
bool get(bitarray b, size_t n);

// Returns the length (count) of a bitarray.
size_t bitarray_len(bitarray b);

#endif // TBC_BITARRAY_H

