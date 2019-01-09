#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <math.h>

START_TEST (check_is_nan)
{
   double x                            = NAN;
   int exit_status                     = EXIT_FAILURE;

    exit_status = is_nan_or_inf(x,(char *)"x",0);
    ck_assert_int_eq(exit_status,EXIT_FIALURE);

}
END_TEST

START_TEST (check_is_inf)
{
   double x                            = INF;
   int exit_status                     = EXIT_FAILURE;

    exit_status = is_nan_or_inf(x,(char *)"x",0);
    ck_assert_int_eq(exit_status,EXIT_FIALURE);

}
END_TEST

Suite * util_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("util");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, check_nan);
    tcase_add_test(tc_core, check_inf);
    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = util_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
