picounit
========

*picounit* is a minimal, yet powerful unit testing framework written in C99.

Features:
--------

- Written in C99 and compatible with C++
- Only two files (header/source) for easy integration into any build system
- Tiny memory and code footprint
- Simple and minimalistic API
- All unit tests are run during execution and failures are indicated
- Optional setup and teardown function support
- Ability to group tests into test suites
- Ability to print test statistics
- Optional color coded output
- Optional time measurement
- MIT licensed

API:
--------

#### PUNIT_ASSERT(expr)

Asserts that the given expression evaluates to `true`. If the expression 
evalutes to `false`, execution of the current test aborts and an error message 
is displayed.

- `expr` - The expression to evaluate

#### PUNIT_ASSERT_STREQ(str1, str2)

Asserts that the given strings are equal. If the strings are not equal,
execution of the enclosing test aborts and an error message is displayed.

- `str1` - A string for comparison
- `str2` - A string for comparison

#### PUNIT_RUN_TEST(p_test)

Runs a unit test function. **IMPORTANT:** The function `p_test` must return 
`true`. The test function has the signature, `bool test_func(void)`.

- `p_test` - The test function to execute

#### PUNIT_RUN_SUITE(p_suite)

Runs a series of unit tests. The test suite function has the signature,
`void suite_func(void)`.

- `p_suite` - The test suite function to run

#### void punit_setup_teardown(punit_setup_fn p_setup, punit_teardown_fn p_teardown);

Sets the current setup and teardown functions. The setup function is called
prior to each unit test and the teardown function after. Either of these
functions can be `NULL`. The setup and teardown functions have the signature,
`void func(void)`.

- `p_setup` - The setup function
- `p_teardown` - The teardown function

#### void punit_clear_setup_teardown(void);

Disables the setup and teardown functions by setting them to `NULL`.

#### punit_colors_on()

Turns terminal colors on. **NOTE:** Off by default.

#### punit_colors_off()

Turns terminal colors off.

#### punit_time_on()

Turns time measurement on. **NOTE:** Off by default.

#### punit_time_off()

Turns time measurement off.

#### punit_print_stats()

Prints test statistics.

Example:
--------

```C
#include <picounit.h>

#include <string.h> /* strcmp */

/*
 * Passing test. Note that the test function declaration returns a boolean value
 * and that the test definition returns true. All test functions must return 
 * true.
 */
bool
test1 ()
{
    PUNIT_ASSERT(2 + 2 == 4);               /* Boolean assertion (ok)
    PUNIT_ASSERT(2 + 2 == 4);               /* Boolean assertion (ok)         */
    PUNIT_ASSERT_STREQ("apples", "apples"); /* String equality assertion (ok) */
    return true;
}

/* Failing test */
bool
test2 ()
{
    PUNIT_ASSERT(2 + 2 != 4);                /* Boolean assertion (fails) */
    PUNIT_ASSERT_STREQ("apples", "oranges"); /* String equality (fails    */
                                             /* but is never called)      */
    return true;
}

/* Mixed results */
bool
test3 ()
{
    PUNIT_ASSERT(2 + 2 == 4);                 /* Boolean assertion (ok) */
    PUNIT_ASSERT_STREQ("apples", "oranges");  /* String equality fails  */
    return true;
}

/* Test suite container function (multiple test suits can be specified. */
void
test_suite ()
{
    PUNIT_RUN_TEST(test1);
    PUNIT_RUN_TEST(test2);
    PUNIT_RUN_TEST(test3);
}

int
main (int argc, char* argv[])
{
    PUNIT_RUN_SUITE(test_suite);
    punit_print_stats(); /* Optional */
    return 0;
}
```

Output:
--------

> ===============================================================<br/>
> Running: test_suite<br/>
> ---------------------------------------------------------------<br/>
> Running: test1 (OK)<br/>
> Running: test2 (FAILED: example1.c (50): 2 + 2 != 4)<br/>
> Running: test3 (FAILED: example1.c (59): "apples"=="oranges")<br/>
> ===============================================================<br/>
> Summary: Passed: 1, Failed: 2, Total: 3, Suites: 1, Asserts: 5<br/>

## License
Copyright (c) 2020 James McLean<br/>
Licensed under the MIT license
