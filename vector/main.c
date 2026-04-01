#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "vector.h"

static void test_vector_init_default(void **state) {
    (void) state;

    vector v = vector_init(int, 0);
    assert_non_null(v);
    assert_int_equal(vector_len(v), 0);
    assert_true(vector_cap(v) > 0);

    vector_free(v);
}


static void test_vector_push_and_get(void **state) {
    (void) state;

    vector v = vector_init(int, 0);

    int a = 10;
    int b = 20;
    int c = 30;

    vector_push(v, a);
    vector_push(v, b);
    vector_push(v, c);

    assert_int_equal(vector_len(v), 3);

    assert_int_equal(vector_get(v, 0, int), a);
    assert_int_equal(vector_get(v, 1, int), b);
    assert_int_equal(vector_get(v, 2, int), c);

    vector_free(v);
}


static void test_vector_set_grows(void **state) {
    (void) state;

    vector v = vector_init(int, 1);

    int x = 42;

    // Setting beyond current length should grow the vector
    vector_set(v, 5, x);

    assert_int_equal(vector_len(v), 6);
    assert_int_equal(vector_get(v, 5, int), x);

    // Everything in between should be NULL
    for (size_t i = 0; i < 5; i++) {
        assert_int_equal(vector_get(v, i, int), 0);
    }

    vector_free(v);
}


static void test_vector_realloc(void **state) {
    (void) state;

    vector v = vector_init(int, 2);
    assert_non_null(v);
    assert_int_equal(vector_len(v), 0);
    assert_int_equal(vector_cap(v), 2);

    // Push a bunch of elements that forces the vector to grow.
    for (size_t i = 0; i < 64; i++) {
        int x = i * 10;
        vector_push(v, x);
    }

    // Check the values.
    for (size_t i = 0; i < 64; i++) {
        assert_int_equal(vector_get(v, i, int), i*10);
    }

}

static void test_vector_store_structs(void **state) {
    (void) state;

    typedef struct {
        int id;
        float value;
        char name[16];
    } Item;

    vector v = vector_init(Item, 0);

    Item a = { .id = 1, .value = 3.14f, .name = "alpha" };
    Item b = { .id = 2, .value = 2.71f, .name = "beta" };
    Item c = { .id = 3, .value = 1.41f, .name = "gamma" };

    vector_push(v, a);
    vector_push(v, b);
    vector_push(v, c);

    assert_int_equal(vector_len(v), 3);

    // Retrieve and compare
    Item ra = vector_get(v, 0, Item);
    Item rb = vector_get(v, 1, Item);
    Item rc = vector_get(v, 2, Item);

    //assert_non_null(ra);
    //assert_non_null(rb);
    //assert_non_null(rc);

    assert_int_equal(ra.id, 1);
    assert_float_equal(ra.value, 3.14f, 0.0001f);
    assert_string_equal(ra.name, "alpha");

    assert_int_equal(rb.id, 2);
    assert_float_equal(rb.value, 2.71f, 0.0001f);
    assert_string_equal(rb.name, "beta");

    assert_int_equal(rc.id, 3);
    assert_float_equal(rc.value, 1.41f, 0.0001f);
    assert_string_equal(rc.name, "gamma");

    vector_free(v);
}

static void test_vector_structs_with_growth(void **state) {
    (void) state;

    typedef struct {
        int id;
        float value;
        char name[16];
    } Item;

    vector v = vector_init(Item, 2);

    Item items[128];
    for (int i = 0; i < 128; i++) {
        items[i].id = i;
        items[i].value = i * 0.5f;
        snprintf(items[i].name, sizeof(items[i].name), "item-%d", i);
        vector_push(v, items[i]);
    }

    for (int i = 0; i < 128; i++) {
        Item r = vector_get(v, i, Item);
        //assert_non_null(r);
        assert_int_equal(r.id, i);
        assert_float_equal(r.value, i * 0.5f, 0.0001f);

        char expected[16];
        snprintf(expected, sizeof(expected), "item-%d", i);
        assert_string_equal(r.name, expected);
    }

    vector_free(v);
}




int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_vector_init_default),
        cmocka_unit_test(test_vector_push_and_get),
        cmocka_unit_test(test_vector_set_grows),
        cmocka_unit_test(test_vector_realloc),
        cmocka_unit_test(test_vector_store_structs),
        cmocka_unit_test(test_vector_structs_with_growth),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

