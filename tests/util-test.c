#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <linux/limits.h>

#include <error.h>
#include <util.h>

static void path_file_concat_null_test_success(void **unused)
{
    const char *path = "path";
    const char *src  = "file";

    assert_null(util_path_file_concat(path, NULL));
    assert_null(util_path_file_concat(NULL, src));
    assert_null(util_path_file_concat(NULL, NULL));
}

static void path_file_concat_overflow_test_success(void **unused)
{
    char path[PATH_MAX];
    char src[PATH_MAX];

    for (int i = 0; i < PATH_MAX; i++)
    {
        path[i] = 'a';
        src[i] = 'b';
    }

    assert_null(util_path_file_concat(path, src));
}

static void path_file_concat_test_success(void **unused)
{
    const char *full_path = "path/file";
    const char *path      = "path";
    const char *src       = "file";

    assert_false(strcmp(full_path, util_path_file_concat(path, src)));
}

static void file_type_str_null_test_success(void **unused)
{
    assert_null(util_file_type_str(-1));
}

static void file_perm_str_test_success(void **unused)
{
    const mode_t perm = (mode_t)16893;
    const char *str   = { "rwxrwxr-x" };

    assert_false(strcmp(str, util_file_perm_str(perm, UTIL_FP_SPECIAL)));
}

static void file_last_mod_time_str_null_test_success(void **unused)
{
    assert_null(util_file_last_mod_time_str(NULL));
}

static void file_name_fstr_null_test_success(void **unused)
{
    assert_null(util_file_name_fstr(NULL, NULL, 0));
}

int main(int argc, char const *argv[])
{
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(path_file_concat_null_test_success),
        cmocka_unit_test(path_file_concat_overflow_test_success),
        cmocka_unit_test(path_file_concat_test_success),
        cmocka_unit_test(file_type_str_null_test_success),
        cmocka_unit_test(file_perm_str_test_success),
        cmocka_unit_test(file_last_mod_time_str_null_test_success),
        cmocka_unit_test(file_name_fstr_null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
