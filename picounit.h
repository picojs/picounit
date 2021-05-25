/** @file picounit.h
 * picounit is a minimal, yet powerful unit testing framework written in C99.
 */

/*=============================================================================
 * MIT License
 *
 * Copyright (c) 2021 James McLean
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
=============================================================================*/

#ifndef PICOUNIT_H
#define PICOUNIT_H

#include <stdbool.h> /* bool, true, false */
#include <stddef.h>  /* NULL */
#include <string.h> /* strcmp */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Asserts that the given expression evaluates to `true` (non-zero). If the
 * expression evalutes to `false` (zero), execution of the current test aborts
 * and an error message is displayed.
 *
 * @param expr The expression to evaluate
 */
#define PUNIT_ASSERT(expr) \
    do  { \
        if (!punit_assert((expr) ? true : false, (#expr), __FILE__, __LINE__)) \
            return false; \
    } while(false)

/**
 * Asserts that the given strings are equal. If the strings are not equal,
 * execution of the enclosing test aborts and an error message is displayed.
 *
 * @param str1 String for comparison
 * @param str2 String for comparison
 */
#define PUNIT_ASSERT_STREQ(str1, str2) \
    do  { \
        if (!punit_assert(0 == strcmp(str1, str2), #str1 "==" #str2, __FILE__, __LINE__)) \
            return false; \
    } while(false)

/**
 * Runs a unit test function. IMPORTANT: The function `p_test` must
 * return `true` (non-zero). The test function has the following signature,
 * `int test_func(void)`.
 *
 * @param p_test The test function to execute
 */
#define PUNIT_RUN_TEST(p_test) (punit_run_test(#p_test, p_test))

/**
 * Runs a series of unit tests. The test suite function has the signature,
 * `void suite_func(void)`.
 *
 * @param p_suite The test suite function to run
 */
#define PUNIT_RUN_SUITE(p_suite) punit_run_suite(#p_suite, p_suite)

/**
 * Functions that are run before a number of unit tests execute.
 */
typedef void (*punit_setup_fn)(void);

/**
 * Functions that are run after a number of unit tests execute.
 */
typedef void (*punit_teardown_fn)(void);

/**
 * Sets the current setup and teardown functions. The setup function is called
 * prior to each unit test and the teardown function after. Either of these
 * functions can be NULL.
 *
 * @param p_setup The setup function
 * @param p_teardown The teardown function
 *
 */
void punit_setup_teardown(punit_setup_fn p_setup, punit_teardown_fn p_teardown);

/**
 * Sets the setup and teardown functions to NULL.
 */
void punit_clear_setup_teardown(void);

/**
 * Turns on terminal colors. NOTE: Off by default.
 */
void punit_colors_on(void);

/**
 * Turns off terminal colors.
 */
void punit_colors_off(void);

/**
 * Turns on time measurement. NOTE: Off by default.
 */
void punit_time_on(void);

/**
 * Turns off time measurement.
 */
void punit_time_off(void);

/**
 * Prints test statistics.
 */
void punit_print_stats(void);

/*
 * NOTE: These functions are not meant to be called directly. Use the macros
 * instead.
 */
typedef bool (*punit_test_fn)(void);
typedef void (*punit_suite_fn)(void);

bool punit_assert(bool b_expr,
                  const char* const p_expr,
                  const char* const p_file,
                  int line);

void punit_run_test(const char* const p_name, punit_test_fn p_test);
void punit_run_suite(const char* const p_name, punit_suite_fn p_suite);

#ifdef __cplusplus
}
#endif

#endif /* PICOUNIT_H */

/* EoF */
