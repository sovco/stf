#include <stdlib.h>
#include <stf/stf.h>

STF_TEST_CASE(expect, success)
{
    STF_EXPECT(true);
}

STF_TEST_CASE(expect, multiple_success)
{
    STF_EXPECT(true);
    STF_EXPECT(true);
    STF_EXPECT(true);
}

STF_TEST_CASE(expect, multiple_success_with_non_showable_failure_msg)
{
    STF_EXPECT(true, .failure_msg = "oh yeaaa.");
    STF_EXPECT(true, .failure_msg = "oh yeaaaaaa.");
    STF_EXPECT(true, .failure_msg = "oh yeaaaaaaaaa.");
}

STF_TEST_CASE(expect, success_with_an_expression)
{
    STF_EXPECT(60 + 9 == 69, .failure_msg = "oh yeaaa.");
}

STF_TEST_CASE(expect, failure)
{
    STF_EXPECT(false);
}

STF_TEST_CASE(expect, multiple_failures)
{
    STF_EXPECT(false);
    STF_EXPECT(false);
    STF_EXPECT(false);
}

STF_TEST_CASE(expect, on_failure_return)
{
    STF_EXPECT(false, .return_on_failure = true);
    STF_EXPECT(true);
    STF_EXPECT(true);
}

STF_TEST_CASE(expect, on_failure_return_with_description)
{
    STF_EXPECT(false, .return_on_failure = true, .failure_msg = "oh noooo.");
    STF_EXPECT(true);
    STF_EXPECT(true);
}

STF_TEST_CASE(expect, multiple_failures_all_with_descriptions)
{
    STF_EXPECT(false, .failure_msg = "oh noooo.");
    STF_EXPECT(false, .failure_msg = "oh noooooooo.");
    STF_EXPECT(false, .failure_msg = "oh noooooooooo.");
}

int main()
{
    STF_RUN_TEST();
    return EXIT_SUCCESS;
}
