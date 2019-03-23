#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include <error.h>
#include <file-info.h>


static void file_info_null_test_success(void **unused)
{
    assert_int_not_equal(ERR_NONE, file_info_print(NULL, NULL, NULL));
}

int main(int argc, char const *argv[])
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(file_info_null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
