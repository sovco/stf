# stf
Single Header Test Framework

# Basic Usage

This is how you declare a test case
```c
STF_TEST_CASE(test, test)
{
    STF_EXPECT(true);
}
```

STF_EXPECT has two arguments the end result (true/false) of the expected value, and options:
```c
typedef struct
{
    const char *failure_msg; // This will be printed out if STF_EXPECT will not meet expectations
    bool return_on_failure; // This option will instruct to leave the test case once expectation is not met
} stf_expect_options;
```

Example of how to use STF_EXPECT options
```c
STF_TEST_CASE(test, test)
{
    STF_EXPECT(true, .failure_msg = "Will write this on failure", .return_on_failure = true);
}
```

To run the tests in your main call STF_RUN_TEST():
```c
int main()
{
    return STF_RUN_TESTS();
}
```

And thats it, simple huh?

# Building Tests

To build tests, run these commands:
```bash

gcc -o project-build test/project-build.c
./project-build
./build/stf-tests

```
