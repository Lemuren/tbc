#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "bitarray.h"

static void test_bitarray_init(void **state) {
    (void) state;

    bitarray b = bitarray_init(128);
    assert_non_null(b);
    assert_int_equal(bitarray_len(b), 128);
    bitarray_destroy(b);

    b = bitarray_init(3);
    assert_non_null(b);
    assert_int_equal(bitarray_len(b), 3);
    bitarray_destroy(b);

    b = bitarray_init(653);
    assert_non_null(b);
    assert_int_equal(bitarray_len(b), 653);
    bitarray_destroy(b);
}

static void test_bitarray_set_and_clear_2n(void **state) {
    (void) state;

    bitarray b = bitarray_init(128);

    // Assert every bit is zero.
    for (int i = 0; i < 128; i++) {
        assert_false(get(b, i));
    }

    // Set a few bits.
    assert_false(set(b, 17));
    assert_false(set(b, 18));
    assert_false(set(b, 19));
    assert_false(set(b, 64));
    assert_false(set(b, 63));

    // Read them back.
    assert_true(get(b, 17));
    assert_true(get(b, 18));
    assert_true(get(b, 19));
    assert_true(get(b, 64));
    assert_true(get(b, 63));

    // Clear some of them.
    assert_true(clear(b, 17));
    assert_true(clear(b, 19));
    assert_true(clear(b, 63));

    // Read them back.
    assert_false(get(b, 17));
    assert_false(get(b, 19));
    assert_false(get(b, 63));

    // Set all the bits back on.
    assert_false(set(b, 17));
    assert_true(set(b, 18));
    assert_false(set(b, 19));
    assert_true(set(b, 64));
    assert_false(set(b, 63));

    // Read them back.
    assert_true(get(b, 17));
    assert_true(get(b, 18));
    assert_true(get(b, 19));
    assert_true(get(b, 64));
    assert_true(get(b, 63));

    bitarray_destroy(b);
}

static void test_bitarray_set_and_clear(void **state) {
    (void) state;

    bitarray b = bitarray_init(500);

    // Assert every bit is zero.
    for (int i = 0; i < 500; i++) {
        assert_false(get(b, i));
    }

    // Set a few bits.
    assert_false(set(b, 17));
    assert_false(set(b, 18));
    assert_false(set(b, 19));
    assert_false(set(b, 64));
    assert_false(set(b, 63));

    // Read them back.
    assert_true(get(b, 17));
    assert_true(get(b, 18));
    assert_true(get(b, 19));
    assert_true(get(b, 64));
    assert_true(get(b, 63));

    // Clear some of them.
    assert_true(clear(b, 17));
    assert_true(clear(b, 19));
    assert_true(clear(b, 63));

    // Read them back.
    assert_false(get(b, 17));
    assert_false(get(b, 19));
    assert_false(get(b, 63));

    // Set all the bits back on.
    assert_false(set(b, 17));
    assert_true(set(b, 18));
    assert_false(set(b, 19));
    assert_true(set(b, 64));
    assert_false(set(b, 63));

    // Read them back.
    assert_true(get(b, 17));
    assert_true(get(b, 18));
    assert_true(get(b, 19));
    assert_true(get(b, 64));
    assert_true(get(b, 63));

    bitarray_destroy(b);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_bitarray_init),
        cmocka_unit_test(test_bitarray_set_and_clear_2n),
        cmocka_unit_test(test_bitarray_set_and_clear),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

