/** \file picounit.h
 * PicoUnit - A minimal, yet powerful, unit testing framework written in C99.
 */

/*==============================================================================
 * Copyright (C) 2019 James McLean
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 * ===========================================================================*/

#ifndef PICO_UNIT_H
#define PICO_UNIT_H

#include <stdbool.h>

/**
 * Assert that the given expression evaluates to true. If the expression
 * evalutes to false, execution of the current test and containing test suite
 * aborts.
 *
 * @param expr The expression to evaluate
 */
#define PICO_ASSERT(p_expr) \
    if (!pico_assert(!!(p_expr), NULL, (#p_expr), __FILE__, __LINE__)) \
        return false

/**
 * Same as the ASSERT macro, however it accepts a message describing the test.
 *
 * @param msg  The message to display
 * @param expr The expression to evaluate
 */
#define PICO_ASSERT_MSG(p_msg, p_expr) \
    if (!pico_assert(!!(p_expr), (p_msg), (#p_expr), __FILE__, __LINE__)) \
        return false

/**
 * Runs a unit test function.
 *
 * @param test The test function to execute
 */
#define PICO_RUN_TEST(p_test) \
    if (!pico_run_test(#p_test, p_test, NULL, NULL)) \
        return false

/**
 * Runs a unit test function with setup and teardown functions.
 *
 * @param test     The test function to execute
 * @param setup    Setup function that is run before the test function
 * @param teardown Teardown function that is run after the test function
 */
#define PICO_RUN_TEST_ST(p_test, p_setup, p_teardown) \
    if (!pico_run_test(#p_test, p_test, p_setup, p_teardown)) \
        return false

/**
 * Runs a series of unit tests.
 *
 * @param suite The test suite to run
 */
#define PICO_RUN_SUITE(p_suite) \
    if (!pico_run_suite(#p_suite, p_suite)) return -1

/*
 * NOTE: These declarations are used internally.
 */
typedef bool (*pico_test_t)(void);
typedef void (*pico_setup_t)(void);
typedef void (*pico_teardown_t)(void);
typedef bool (*pico_suite_t)(void);

bool pico_assert(bool passed,
                 const char* const p_msg,
                 const char* const p_expr,
                 const char* const p_file,
                 int line);

bool pico_run_test(const char* const p_name,
                   pico_test_t p_test,
                   pico_setup_t p_setup,
                   pico_teardown_t p_teardown);

bool pico_run_suite(const char* const p_name, pico_suite_t p_suite);

#endif // PICO_UNIT_H

/* EoF */
