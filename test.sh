#!/bin/sh

PROJECT_ROOT="$(cd -- "$(dirname -- "$0")" && pwd)"
BYGG="/home/het/repos/bygg/bygg"
MODULES="vector map bitarray"



# Run shellcheck on this script.
shellcheck --norc -o all "${PROJECT_ROOT}/test.sh" || exit 1

# Build each test.
rm -rf "${PROJECT_ROOT}/build/"
for mod in ${MODULES}; do
    echo "Building ${mod}..."
    "${BYGG}" "--quiet" "${PROJECT_ROOT}/${mod}" "${PROJECT_ROOT}/build/${mod}" || exit 1
done

# Run each test.
for mod in ${MODULES}; do
    echo "=== TESTING ${mod} ==="
    "${PROJECT_ROOT}/build/${mod}/a.out" || exit 1
done
