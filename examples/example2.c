/*=============================================================================
 * MIT License
 *
 * Copyright (c) 2020 James McLean
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

#include <picounit.h>

#include <string.h> /* strcmp */

static unsigned g_fix = 0;

/* All assertions pass in this test. */
int test_passing1 ()
{
    PUNIT_ASSERT(1);
    PUNIT_ASSERT(42 == 42);
    PUNIT_ASSERT(0 == strcmp("towel", "towel"));
    return 1;
}

/* Sets up fixture for (called before test). */
void test_setup ()
{
    g_fix = 42;
}

/* Resets fixture (called after test). */
void test_teardown ()
{
    g_fix = 0;
}

/*
 * All assertions pass in this test. Checks the value of the fixture initialized
 * in the test setup function.
 */
int test_passing2 ()
{
    PUNIT_ASSERT(42 == g_fix);
    PUNIT_ASSERT(0 == strcmp("frog", "frog"));
    return 1;
}

/* Test containing failing assertion. */
int test_failing1 ()
{
    PUNIT_ASSERT(1);
    PUNIT_ASSERT(24 == 42); /* Fails here */
    PUNIT_ASSERT(1);        /* Never called */
    return 1;
}

/* Another test containing a failed assertion. */
int test_failing2 ()
{
    PUNIT_ASSERT(0 == strcmp("frog", "butterfly")); /* Fails here */
    PUNIT_ASSERT(1);                                /* Never called */
    return 1;
}

/* A test suite containing two passing and one failing test. */
void test_suite1 ()
{
    PUNIT_RUN_TEST(test_passing1);
    PUNIT_RUN_TEST_ST(test_passing2, test_setup, test_teardown);
    PUNIT_RUN_TEST(test_failing1);
}

/* A test suite containing two passing and one failing test. */
void test_suite2 ()
{
    PUNIT_RUN_TEST(test_passing1);
    PUNIT_RUN_TEST(test_failing2);
    PUNIT_RUN_TEST(test_passing1);
}

/* Run all test suites and print test statistics. */
int main (int argc, char** argv)
{
    punit_colors_on();
    PUNIT_RUN_SUITE(test_suite1);
    PUNIT_RUN_SUITE(test_suite2);
    punit_print_stats();
    return 0;
}

/* EoF */
