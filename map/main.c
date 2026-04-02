#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <string.h>

#include "map.h"

static void test_map_init(void **state) {
    (void) state;

    hashmap m = map_init(char*, int, 0);
    assert_non_null(m);
    assert_int_equal(map_len(m), 0);
    assert_true(map_cap(m) > 0);
    map_free(m);

    struct Item {
        char *name;
        int age;
    };
    hashmap h = map_init(struct Item, int, 32);
    assert_non_null(h);
    assert_int_equal(map_len(h), 0);
    assert_int_equal(map_cap(h), 32);
    map_free(h);
}

static void test_map_get_empty(void **state) {
    (void) state;

    hashmap m = map_init(int, int, 16);

    int key = 42;
    void *res = map_get(m, &key);

    assert_null(res);

    map_free(m);
}

static void test_map_set_and_get_int(void **state) {
    (void) state;

    hashmap m = map_init(int, int, 16);

    int key = 10;
    int val = 123;

    map_set(m, &key, &val);

    assert_int_equal(map_len(m), 1);

    int *out = map_get(m, &key);
    assert_non_null(out);
    assert_int_equal(*out, 123);

    map_free(m);
}

static void test_map_overwrite(void **state) {
    (void) state;

    hashmap m = map_init(int, int, 16);

    int key = 5;
    int val1 = 100;
    int val2 = 200;

    map_set(m, &key, &val1);
    map_set(m, &key, &val2);

    assert_int_equal(map_len(m), 1);

    int *out = map_get(m, &key);
    assert_non_null(out);
    assert_int_equal(*out, 200);

    map_free(m);
}

static void test_map_overwrite_string_keys(void **state) {
    (void) state;

    hashmap m = map_init(char[16], int, 16);

    char key1[16] = "hello";
    char key2[16] = "hello";
    int val1 = 100;
    int val2 = 200;

    map_set(m, &key1, &val1);
    map_set(m, &key2, &val2);

    assert_int_equal(map_len(m), 1);

    int *out = map_get(m, &key1);
    assert_non_null(out);
    assert_int_equal(*out, 200);

    map_free(m);
}



static void test_map_struct_keys(void **state) {
    (void) state;

    typedef struct {
        int x;
        float y;
    } Foo;

    hashmap m = map_init(Foo, int, 16);

    Foo key = { .x = 1, .y = 2.0f };
    int val = 999;

    map_set(m, &key, &val);

    int *out = map_get(m, &key);
    assert_non_null(out);
    assert_int_equal(*out, 999);

    map_free(m);
}

static void test_map_string_keys(void **state) {
    (void) state;

    hashmap m = map_init(char[16], int, 16);

    char key[16] = "hello";
    int val = 42;

    map_set(m, key, &val);

    int *out = map_get(m, key);
    assert_non_null(out);
    assert_int_equal(*out, 42);

    map_free(m);
}

static void test_map_many_key_value_pairs(void **state) {
    (void) state;

    hashmap m = map_init(int, int, 16);

    int keys[] = {1, 2, 3, 4};
    int vals[] = {10, 20, 30, 40};

    for (int i = 0; i < 4; i++) {
        map_set(m, &keys[i], &vals[i]);
    }

    // Now check that each key retrieves its own value
    for (int i = 0; i < 4; i++) {
        int *out = map_get(m, &keys[i]);
        assert_non_null(out);
        assert_int_equal(*out, vals[i]);
    }

    map_free(m);
}


static void test_map_many_key_value_pairs_structs(void **state) {
    (void) state;

    typedef struct {
        int x;
        float y;
    } Foo;

    hashmap m = map_init(Foo, char[64], 16);

    Foo key1 = { .x = 1, .y = 1.0f };
    Foo key2 = { .x = 2, .y = 2.0f };
    Foo key3 = { .x = 3, .y = 3.0f };
    Foo key4 = { .x = 4, .y = 4.0f };
    Foo keys[] = {key1, key2, key3, key4};
    char vals[64][64] = {"hello", "there", "my", "friend"};

    for (int i = 0; i < 4; i++) {
        map_set(m, &keys[i], &vals[i]);
    }

    // Now check that each key retrieves its own value
    for (int i = 0; i < 4; i++) {
        char* out = map_get(m, &keys[i]);
        assert_non_null(out);
        assert_string_equal(out, vals[i]);
    }

    map_free(m);
}

static void test_map_many_key_value_pairs_strings(void **state) {
    (void) state;

    hashmap m = map_init(char*, char*, 16);

    char keys[64][64] = {"a", "b", "c", "d"};
    char vals[64][64] = {"hello", "there", "my", "friend"};

    for (int i = 0; i < 4; i++) {
        map_set(m, &keys[i], &vals[i]);
    }

    // Now check that each key retrieves its own value
    for (int i = 0; i < 4; i++) {
        char *out = map_get(m, &keys[i]);
        assert_non_null(out);
        assert_string_equal(out, vals[i]);
    }

    map_free(m);
}


static void test_map_collision_resolution(void **state) {
    (void) state;

    hashmap m = map_init(int, int, 2); // tiny cap to force collisions

    int k1 = 1, v1 = 10;
    int k2 = 3, v2 = 30;

    map_set(m, &k1, &v1);
    map_set(m, &k2, &v2);

    assert_int_equal(map_len(m), 2);

    assert_int_equal(*(int*)map_get(m, &k1), 10);
    assert_int_equal(*(int*)map_get(m, &k2), 30);

    map_free(m);
}


//static void test_map_resize(void **state) {
//    (void) state;
//
//    hashmap m = map_init(int, int, 4);
//
//    for (int i = 0; i < 100; i++) {
//        map_set(m, &i, &i);
//    }
//
//    assert_true(map_cap(m) > 4);
//    assert_int_equal(map_len(m), 100);
//
//    for (int i = 0; i < 100; i++) {
//        int *out = map_get(m, &i);
//        assert_non_null(out);
//        assert_int_equal(*out, i);
//    }
//
//    map_free(m);
//}





int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_map_init),
        cmocka_unit_test(test_map_get_empty),
        cmocka_unit_test(test_map_set_and_get_int),
        cmocka_unit_test(test_map_overwrite),
        cmocka_unit_test(test_map_overwrite_string_keys),
        cmocka_unit_test(test_map_struct_keys),
        cmocka_unit_test(test_map_string_keys),
        cmocka_unit_test(test_map_many_key_value_pairs),
        cmocka_unit_test(test_map_many_key_value_pairs_structs),
        cmocka_unit_test(test_map_many_key_value_pairs_strings),
        cmocka_unit_test(test_map_collision_resolution),
        //cmocka_unit_test(test_map_resize),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

