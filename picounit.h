/** \file picounit.h
 * PicoUnit is a minimal, yet powerful unit testing framework written in ANSI C.
 * Due to its small footprint, PicoUnit is suitable for embedded as well as
 * general development.
 */

/*=============================================================================
 * MIT License
 *
 * Copyright (c) 2019 James McLean
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

#ifndef PICO_UNIT_H
#define PICO_UNIT_H

#include <stddef.h>  /* NULL */

/**
 * Asserts that the given expression evaluates to `true` (non-zero). If the 
 * expression evalutes to `false` (zero), execution of the current test aborts 
 * and an error message is displayed.
 *
 * @param expr The expression to evaluate
 */
#define PICO_ASSERT(expr) \
    if (!pico_assert((expr) ? 1 : 0, (#expr), __FILE__, __LINE__)) \
        return 0

/**
 * Asserts that the given strings are equal. If the strings are not equal,
 * execution of the current test aborts and an error message is displayed.
 *
 * @param p_left_str  A string to compare
 * @param p_right_str A string to compare
 */
#define PICO_ASSERT_STR_EQ(p_left_str, p_right_str) \
    if (!pico_assert_str_eq(p_left_str, p_right_str, __FILE__, __LINE__)) \
        return 0

/**
 * Runs a unit test function. IMPORTANT: The function `p_test` must
 * return `true` (non-zero).
 *
 * @param p_test The test function to execute
 */
#define PICO_RUN_TEST(p_test) \
    pico_run_test(#p_test, p_test, NULL, NULL)

/**
 * Runs a unit test function with setup and teardown functions. Either one of
* `p_setup` or `p_teardown` can be `NULL`.
 *
 * @param p_test     The test function to execute
 * @param p_setup    Setup function that is run before the test function
 * @param p_teardown Teardown function that is run after the test function
 */
#define PICO_RUN_TEST_ST(p_test, p_setup, p_teardown) \
    pico_run_test(#p_test, p_test, p_setup, p_teardown)

/**
 * Runs a series of unit tests.
 *
 * @param p_suite The test suite function to run
 */
#define PICO_RUN_SUITE(p_suite) pico_run_suite(#p_suite, p_suite)

/**
 * Prints test statistics.
 */
#define PICO_PRINT_STATS() pico_print_stats()

#ifdef __cplusplus
extern "C" {
#endif

/*
 * NOTE: These declarations are used internally and should not be used directly.
 */
typedef int  (*pico_test_t)(void);
typedef void (*pico_setup_t)(void);
typedef void (*pico_teardown_t)(void);
typedef void (*pico_suite_t)(void);

int pico_assert(int b_expr,
                const char* const p_expr,
                const char* const p_file,
                int line);

int pico_assert_str_eq(const char* const p_left_str,
                       const char* const p_right_str,
                       const char* const p_file,
                       int line);

void pico_run_test(const char* const p_name,
                   pico_test_t p_test,
                   pico_setup_t p_setup,
                   pico_teardown_t p_teardown);

void pico_run_suite(const char* const p_name,
                    pico_suite_t p_suite);

void pico_print_stats();

#ifdef __cplusplus
}
#endif

#endif /* PICO_UNIT_H */

/* EoF */
