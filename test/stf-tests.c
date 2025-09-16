#include <stdlib.h>
#include <stf/stf.h>

STF_TEST_CASE(expect, success)
{
    stf_expect(true);
}

STF_TEST_CASE(expect, multiple_success)
{
    stf_expect(true);
    stf_expect(true);
    stf_expect(true);
}

STF_TEST_CASE(expect, multiple_success_with_non_showable_failure_msg)
{
    stf_expect(true, .failure_msg = "oh yeaaa.");
    stf_expect(true, .failure_msg = "oh yeaaaaaa.");
    stf_expect(true, .failure_msg = "oh yeaaaaaaaaa.");
}

STF_TEST_CASE(expect, failure)
{
    stf_expect(false);
}

STF_TEST_CASE(expect, multiple_failures)
{
    stf_expect(false);
    stf_expect(false);
    stf_expect(false);
}

STF_TEST_CASE(expect, on_failure_return)
{
    stf_expect(false, .return_on_failure = true);
    stf_expect(true);
    stf_expect(true);
}

STF_TEST_CASE(expect, on_failure_return_with_description)
{
    stf_expect(false, .return_on_failure = true, .failure_msg = "oh noooo.");
    stf_expect(true);
    stf_expect(true);
}

STF_TEST_CASE(expect, multiple_failures_all_with_descriptions)
{
    stf_expect(false, .failure_msg = "oh noooo.");
    stf_expect(false, .failure_msg = "oh noooooooo.");
    stf_expect(false, .failure_msg = "oh noooooooooo.");
}

int main()
{
    STF_RUN_TEST();
    return EXIT_SUCCESS;
}
