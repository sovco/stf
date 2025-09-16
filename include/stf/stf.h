#ifndef STF_H
#define STF_H

#include <stdio.h>
#include <stdbool.h>

#define ANSI_RESET_ALL "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

typedef void (*test_func)(void *caller);

typedef struct
{
    const char *failure_msg;
    struct stf_expect_faults *next;
    int line_num;
} stf_expect_faults;

typedef struct
{
    const char *failure_msg;
    bool return_on_failure;
} stf_expect_options;

typedef struct
{
    const char *group;
    const char *description;
    test_func executor;
    struct stf_test_case *next;
    stf_expect_faults *expect_faults;
} stf_test_case;

typedef struct
{
    stf_test_case *cases;
    int count;
} stf_test_suite;

static stf_test_suite TEST_CASES = { 0 };

static inline void stf_register_case(stf_test_suite *suite, stf_test_case new_case)
{
    stf_test_case **test_case = &suite->cases;
    while (*test_case != NULL) {
        test_case = (stf_test_case **)&((*test_case)->next);
    }
    *test_case = malloc(sizeof(**test_case));
    **test_case = new_case;
    TEST_CASES.count++;
}

static inline void stf_register_test_case_failure_msg(stf_test_case *test_case, const char *msg, int line_num)
{
    stf_expect_faults **error_msg = &test_case->expect_faults;
    while (*error_msg != NULL) {
        error_msg = (stf_expect_faults **)&((*error_msg)->next);
    }
    *error_msg = malloc(sizeof(**error_msg));
    **error_msg = (stf_expect_faults){
        .failure_msg = msg,
        .next = NULL,
        .line_num = line_num
    };
}

static inline void stf_fault_clean_up(stf_test_case *test_case)
{
    stf_expect_faults *fault = test_case->expect_faults;
    while (fault != NULL) {
        stf_expect_faults *tmp = (stf_expect_faults *)fault->next;
        free(fault);
        fault = tmp;
    }
}

static inline void stf_clean_up(stf_test_suite *suite)
{
    stf_test_case *test_case = suite->cases;
    while (test_case != NULL) {
        stf_test_case *tmp = (stf_test_case *)test_case->next;
        stf_fault_clean_up(test_case);
        free(test_case);
        test_case = tmp;
    }
}

#define STF_TEST_CASE(grp, desc)                                                                                                                                               \
    void grp##desc##_test(void *test_info);                                                                                                                                    \
    void __attribute__((constructor)) register_##grp##desc(void)                                                                                                               \
    {                                                                                                                                                                          \
        stf_register_case(&TEST_CASES, (stf_test_case){ .executor = (test_func)&grp##desc##_test, .next = NULL, .group = #grp, .description = #desc, .expect_faults = NULL }); \
    }                                                                                                                                                                          \
    void grp##desc##_test(void *test_info)

#define STF_RUN_TEST()                                                                                                                                                                                     \
    do {                                                                                                                                                                                                   \
        printf(ANSI_COLOR_GREEN "Running total of %d tests...\n" ANSI_RESET_ALL, TEST_CASES.count);                                                                                                        \
        for (stf_test_case *test_case = TEST_CASES.cases; test_case != NULL; test_case = (stf_test_case *)test_case->next) {                                                                               \
            test_case->executor((void *)test_case);                                                                                                                                                        \
            if (test_case->expect_faults == NULL) {                                                                                                                                                        \
                printf(ANSI_COLOR_GREEN "    [PASSED] %s.%s\n" ANSI_RESET_ALL, test_case->group, test_case->description);                                                                                  \
                continue;                                                                                                                                                                                  \
            }                                                                                                                                                                                              \
            printf(ANSI_COLOR_GREEN "    [" ANSI_COLOR_RED "FAILED" ANSI_RESET_ALL ANSI_COLOR_GREEN "] %s.%s\n" ANSI_RESET_ALL, test_case->group, test_case->description);                                 \
            for (stf_expect_faults *failure_msg = test_case->expect_faults; failure_msg != NULL; failure_msg = (stf_expect_faults *)failure_msg->next) {                                                   \
                if (failure_msg->failure_msg) {                                                                                                                                                            \
                    printf("        " ANSI_COLOR_RED "At line" ANSI_COLOR_GREEN " %d" ANSI_COLOR_RED ", expectations were not met: %s\n" ANSI_RESET_ALL, failure_msg->line_num, failure_msg->failure_msg); \
                    continue;                                                                                                                                                                              \
                }                                                                                                                                                                                          \
                printf("        " ANSI_COLOR_RED "At line" ANSI_COLOR_GREEN " %d" ANSI_COLOR_RED ", expectations were not met.\n" ANSI_RESET_ALL, failure_msg->line_num);                                  \
            }                                                                                                                                                                                              \
        }                                                                                                                                                                                                  \
        stf_clean_up(&TEST_CASES);                                                                                                                                                                         \
    } while (0)

#define stf_expect(expr, ...)                                                                          \
    do {                                                                                               \
        int line = __LINE__;                                                                           \
        stf_expect_options options = (stf_expect_options){ __VA_ARGS__ };                              \
        if (!expr) {                                                                                   \
            stf_register_test_case_failure_msg((stf_test_case *)test_info, options.failure_msg, line); \
            if (options.return_on_failure) {                                                           \
                return;                                                                                \
            }                                                                                          \
        }                                                                                              \
    } while (0)

#endif// STF_H
