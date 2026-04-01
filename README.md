# tbc — tiny building components for C

tbc is a small, growing collection of single‑purpose C modules:
dynamic arrays, stacks, queues, hashmaps, trees, and other little building
blocks you can drop into any project.

These modules are intended to be used with
[bygg](https://github.com/Lemuren/bygg).

## Using tbc Modules
Inside each directory (e.g. `vector` there is a main .c file which consists
of unit tests and the source of the module itself, named the same as the
parent directory. It is this subdiretory you want to copy.

To use a tbc module, simply drop the directory into your project,
update `.bygg` files to include it and `#include "vector.h"` in
relevant files.

## Testing tbc
The unit tests themselves live in the `main.c` file of each tbc module.
There's a small helper shell script to build and run all the tests.
You'll also need `shellcheck` to check the script itself.
