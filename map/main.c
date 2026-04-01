#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "map.h"

//static void test_vector_init_default(void **state) {
//    (void) state;
//
//    vector v = vector_init(int, 0);
//    assert_non_null(v);
//    assert_int_equal(vector_len(v), 0);
//    assert_true(vector_cap(v) > 0);
//
//    vector_free(v);
//}


int main(void) {
    const struct CMUnitTest tests[] = {
        //cmocka_unit_test(test_vector_init_default),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

