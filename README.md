PicoUnit
========

PicoUnit is a minimal, yet powerful unit testing framework written in ANSI C.
Due to its small footprint, PicoUnit is suitable for embedded as well as general
development.

Features:
--------

- Written in pure ANSI C, but also compatible with C++
- Only two files (header/source) for easy integration into any build system
- Tiny memory and code footprint
- Simple and minimalistic API
- All unit tests are run during execution and failures are indicated
- Optional setup and teardown function support
- Ability to group tests into test suites
- Ability to print test statistics
- Color coded output


API:
--------

#### PICO_ASSERT(expr)

Asserts that the given expression evaluates to `true` (non-zero). If the
expression evalutes to `false` (zero), execution of the current test aborts and
an error message is displayed.

- expr - The expression to evaluate

#### PICO_ASSERT_STR_EQ(p_left_str, p_right_str)

Asserts that the given strings are equal. If the strings are not equal,
execution of the current test aborts and an error message is displayed.

- p_left_str  A string to compare
- p_right_str A string to compare

#### PICO_RUN_TEST(p_test)

Runs a unit test function. **IMPORTANT**: The function `p_test` must
return `true` (non-zero).

- p_test The test function to execute

#### PICO_RUN_TEST_ST(p_test, p_setup, p_teardown)

Runs a unit test function with setup and teardown functions. Either one of
`p_setup` or `p_teardown` can be `NULL`.

- p_test The test function to execute
- p_setup Setup function that is run before the test function
- p_teardown Teardown function that is run after the test function

#### PICO_RUN_SUITE(p_suite)

Runs a series of unit tests.

- p_suite The test suite function to run

#### PICO_PRINT_STATS()

Prints test statistics.

Example:
--------

```C
#include <picounit.h>

/*
 * Passing test. Note that the test function declaration returns an integer
 * value and that the test definition returns true. All test functions must
 * return a non-zero value.
 */
int
test1 ()
{
    PICO_ASSERT(2 + 2 == 4);                /* Simple boolean assertion (ok)  */
    PICO_ASSERT_STR_EQ("apples", "apples"); /* String equality assertion (ok) */
    return 1;
}

/* Failing test */
int
test2 ()
{
    PICO_ASSERT(2 + 2 != 4);                 /* Boolean assertion (fails) */
    PICO_ASSERT_STR_EQ("apples", "oranges"); /* String equality assertion */
                                             /* (fails but never called)  */
    return 1;
}

/* Mixed results */
int
test3 ()
{
    PICO_ASSERT(2 + 2 == 4);                 /* Simple boolean assertion (ok) */
    PICO_ASSERT_STR_EQ("apples", "oranges"); /* String equality assertion */
                                             /* (fails)                   */
    return 1;
}

/* Test suite container function (multiple test suits can be specified. */
void
test_suite()
{
    PICO_RUN_TEST(test1);
    PICO_RUN_TEST(test2);
    PICO_RUN_TEST(test3);
}

int
main (int argc, char* argv[])
{
    PICO_RUN_SUITE(test_suite);
    PICO_PRINT_STATS(); /* Optional */
    return 0;
}
```

## License
Copyright (c) 2019 James McLean
Licensed under the MIT license
